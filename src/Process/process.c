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
    //printf("dead PID: %d", current_process);
    process_table[current_process].state = P_TERMINATE;
    while(1);
}

// void process_entry(){
//     process_table[current_process].entry();
//     process_kill();
// }

void process_save(){
    if(current_process == -1) return;
    process_table[current_process].esp = current_esp;
    if(process_table[current_process].state == P_RUNNING) process_table[current_process].state = P_READY;
}

void process_switch(){
    int next = current_process == -1 ? 0 :schedule();

    process_table[next].state = P_RUNNING;
    unsigned int new = process_table[next].esp;

    current_process = next;
    switch_context(new, (unsigned int)process_table[next].PD);
}

void process_spawn(void (*entry)(void)){
    cli();
    if(process_count >= MAX_PROCESS) {sti(); return;}
    unsigned int* PD = create_page_directory();
    unsigned int* phy_stack = pmm_alloc(1);

    //printf("Stack at: %x\n", (unsigned int)phy_stack);
    //printf("Function pointer -> %x\n", (unsigned int)entry);
    //printf("Page Directory -> %x\n", (unsigned int)PD);
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

    for(int i=0; i<MAX_PROCESS; i++){
        if(process_table[i].state == P_FREE){
            process_table[i].k_esp = kernel_esp;
            process_table[i].state = P_NEW;
            process_table[i].stack_base = (unsigned int)PROCESS_STACK_BASE;
            process_table[i].stack_top = (unsigned int)PROCESS_STACK_TOP;
            process_table[i].heap_start = HEAP_BASE;
            process_table[i].heap_end = HEAP_BASE;
            process_table[i].PD = PD;
            Emalloc_init(&process_table[i]);
            load_elf(_binary___build_hello_elf_start, &process_table[i]);\
            *(--esp) = (unsigned int)process_table[i].eip;

            *(--esp) = 0; // EAX
            *(--esp) = 0; // ECX
            *(--esp) = 0; // EDX
            *(--esp) = 0; // EBX
            *(--esp) = 0; // OLD ESP
            *(--esp) = 0; // EBP
            *(--esp) = 0; // ESI
            *(--esp) = 0; // EDI
            process_table[i].esp = PROCESS_STACK_TOP - (unsigned int)((unsigned int)phy_stack + PAGE_SIZE - (unsigned int)esp);
            process_count++;
            printf("Entry: %x\n", process_table[i].eip);
            printf("PID: %d\n", process_table[i].pid);
            unsigned int old_cr3;

            asm volatile(
                "mov %%cr3, %0"
                : "=r"(old_cr3)
            );

            asm volatile(
                "mov %0, %%cr3"
                :
                : "r"(PD)
                : "memory"
            );

            unsigned char* code =
            (unsigned char*)process_table[i].eip;

            printf(
                "%x %x %x %x\n",
                code[0],
                code[1],
                code[2],
                code[3]
            );

            asm volatile(
                "mov %0, %%cr3"
                :
                : "r"(old_cr3)
                : "memory"
            );
            printf("Process ESP = %x\n", process_table[i].esp);
            //for(int i=0; i<1000000000; i++){}
            sti();
            return;
        }
    }
    sti();
    
}   