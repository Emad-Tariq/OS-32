#include "process.h"
#include "../Memory/pmm.h"
#include "../Terminal/terminal.h"

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

void process_switch(){
    int next = (current_process+1) % MAX_PROCESS;

    //Use a scheduler later here,this is just a dummy basic RR for now
    while(process_table[next].state != P_READY){
        next = (++next) % MAX_PROCESS;
        if(next == current_process) return;
    }

    if(current_process != -1){
        process_table[current_process].state = P_READY;
        process_table[current_process].esp = current_esp;
    }
    process_table[next].state = P_RUNNING;

    unsigned int new = process_table[next].esp;
    current_process = next;

    switch_context(new);
}

void process_spawn(void (*entry)(void)){
    if(process_count >= MAX_PROCESS) return;
    unsigned int* stack = (unsigned int*)pmm_alloc(1);
    unsigned int* esp = (unsigned int*)((unsigned int)stack + PAGE_SIZE);
    printf("Stack at: %x\n", (unsigned int)stack);
    printf("Function pointer -> %x\n", (unsigned int)entry);

    *(--esp) = 0x202;
    *(--esp) = 0x08;
    *(--esp) = (unsigned int)entry;

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
            process_table[i].esp = (unsigned int)esp;
            process_table[i].state = P_READY;
            return;
        }
    }
}