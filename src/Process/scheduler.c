#include "scheduler.h"
#include "process.h"
#include "../Memory/pmm.h"
#include "../Memory/paging.h"
#include "../Terminal/terminal.h"

volatile unsigned int system_ticks;

void scheduler_init(){
    system_ticks = 0;
}

int schedule(){
    int next = (current_process + 1) % MAX_PROCESS;
    while(process_table[next].state != P_READY && process_table[next].state != P_NEW){
        next = (next+1) % MAX_PROCESS;
        if(next == current_process) return 0;
    }
    return next;
}

void update(){
    for(int i=0; i<MAX_PROCESS; i++){
        //if(i == current_process) continue;
        if(process_table[i].state == P_TERMINATE){

            for(int j=0; j<4; j++){
                unsigned int phy = get_phy_addr(process_table[i].PD, process_table[i].stack_base + j*PAGE_SIZE);
                unmap_page(process_table[i].PD, process_table[i].stack_base + j*PAGE_SIZE);
                pmm_free(phy, 1);
            }
            for(int j=0; j<(process_table[i].heap_end - process_table[i].heap_start) / PAGE_SIZE; j++){
                unsigned int virt = process_table[i].heap_start + j*PAGE_SIZE;
                unsigned phy = get_phy_addr(process_table[i].PD, virt);

                unmap_page(process_table[i].PD, virt);
                pmm_free(phy, 1);
            }

            pmm_free((unsigned int)process_table[i].PD, 1);
            process_table[i].state = P_FREE;
            process_count--;
            //printf("Process %d freed\n", process_table[i].pid);
        }
        else if(process_table[i].state == P_BLOCKED){
            process_table[i].state = system_ticks >= process_table[i].wakeup_tick ? P_READY : P_BLOCKED;
        }
    }
}

void sleep(unsigned int ticks){
    process_table[current_process].state = P_BLOCKED;
    process_table[current_process].wakeup_tick = system_ticks + ticks;
    while(process_table[current_process].state == P_BLOCKED);
}