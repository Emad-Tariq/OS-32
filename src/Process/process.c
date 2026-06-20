#include "process.h"
#include "../Memory/pmm.h"
#include "../Terminal/terminal.h"
#include "scheduler.h"
#include "../Memory/paging.h"

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
    process_table[current_process].entry();
    process_kill();
}

void process_switch(){
    //Use a scheduler later here,this is just a dummy basic RR for now
    int next = current_process == -1 ? 0 :schedule();
    if(current_process != -1){
        if(process_table[current_process].state == P_RUNNING){
            process_table[current_process].state = P_READY;
        }
        process_table[current_process].esp = current_esp;
    }
    process_table[next].state = P_RUNNING;
    unsigned int new = process_table[next].esp;

    current_process = next;
    switch_context(new, (unsigned int)process_table[next].PD);
}

void process_spawn(void (*entry)(void)){
    //if(process_count >= MAX_PROCESS) return;
    unsigned int* PD = create_page_directory();
    unsigned int* phy_stack = pmm_alloc(1);

    printf("Stack at: %x\n", (unsigned int)phy_stack);
    printf("Function pointer -> %x\n", (unsigned int)entry);
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
    *(--esp) = (unsigned int)process_entry;

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
            process_table[i].esp = PROCESS_STACK_TOP - (unsigned int)((unsigned int)phy_stack + PAGE_SIZE - (unsigned int)esp);
            process_table[i].state = P_NEW;
            process_table[i].entry = entry;
            process_table[i].stack_base = (unsigned int)PROCESS_STACK_BASE;
            process_table[i].stack_top = (unsigned int)PROCESS_STACK_TOP;
            process_table[i].PD = PD;
            return;
        }
    }
}   