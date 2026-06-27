#include "process.h"

PCB process_table[MAX_PROCESS];
int process_count;
int current_process;

void process_init(){
    process_count = 0;
    current_process = -1;
    for(int i=0; i<MAX_PROCESS; i++){
        process_table[i].pid = i;
        process_table[i].state = P_FREE;
    }
}

void process_kill(){
    process_table[current_process].state = P_TERMINATE;
    while(1);
}

void process_entry(){
    int (*entry)(void) = (int (*)(void))process_table[current_process].e_entry;
    int status = entry();
    process_kill();
}

void process_save(){
    if(current_process == -1) return;
    process_table[current_process].esp = current_esp;
    if(process_table[current_process].state == P_RUNNING) process_table[current_process].state = P_READY;
}

void process_switch(){
    int next = current_process == -1 ? 0 : schedule();

    process_table[next].state = P_RUNNING;
    unsigned int new = process_table[next].esp;

    current_process = next;
    send_eoi(0);
    switch_context(new, (unsigned int)process_table[next].PD);
}

void process_spawn(const char* fname){
    //cli();
    if(process_count >= MAX_PROCESS) {sti(); return;}

    FileEntry* file = fs_find(fname);
    if(!file){
        printf("fatal: no such file\n");
        return;
    }
    unsigned int pages = (512 * file->sectors + PAGE_SIZE - 1) / PAGE_SIZE;
    unsigned char* image = pmm_alloc(pages);
    ata_read(file->start_lba, image, file->sectors);

    unsigned int* PD = create_page_directory();
    unsigned int* phy_stack = pmm_alloc(1);

    printf("Stack at: %x\n", (unsigned int)phy_stack);
    printf("Page Directory -> %x\n", (unsigned int)PD);
    map_page(
        PD,
        PROCESS_STACK_TOP - PAGE_SIZE,
        (unsigned int) phy_stack,
        PAGE_PRESENT | PAGE_WRITABLE
    );
    for(int i = 0; i < 3; i++)
    {
        void* page = pmm_alloc(1);

        map_page(
            PD,
            PROCESS_STACK_BASE + i * PAGE_SIZE,
            (unsigned int)page,
            PAGE_PRESENT | PAGE_WRITABLE
        );
    }
    unsigned int* esp = (unsigned int*)((unsigned int)phy_stack + PAGE_SIZE);

    *(--esp) = 0x202;
    *(--esp) = 0x08;

    //*(--esp) = (unsigned int)process_table[i].eip;
    *(--esp) = (unsigned int)&process_entry;

    *(--esp) = 0; // EAX
    *(--esp) = 0; // ECX
    *(--esp) = 0; // EDX
    *(--esp) = 0; // EBX
    *(--esp) = 0; // OLD ESP
    *(--esp) = 0; // EBP
    *(--esp) = 0; // ESI
    *(--esp) = 0; // EDI

    for(int i=0; i<MAX_PROCESS; i++){
        if(process_table[i].state == P_FREE){
            process_table[i].k_esp = kernel_esp;
            process_table[i].k_pd = (unsigned int)kernel_pd;
            process_table[i].state = P_NEW;
            process_table[i].stack_base = (unsigned int)PROCESS_STACK_BASE;
            process_table[i].stack_top = (unsigned int)PROCESS_STACK_TOP;
            process_table[i].heap_start = HEAP_BASE;
            process_table[i].heap_end = HEAP_BASE;
            process_table[i].PD = PD;
            process_table[i].eip = (unsigned int)&process_entry;
            process_table[i].esp = PROCESS_STACK_TOP - (unsigned int)((unsigned int)phy_stack + PAGE_SIZE - (unsigned int)esp);
            process_table[i].elf_image = (unsigned int)image;
            process_count++;
            Emalloc_init(&process_table[i]);
            load_elf(image, &process_table[i]);
            //sti();
            return;
        }
    }
    //sti();
    
}   