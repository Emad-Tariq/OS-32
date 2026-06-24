#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESS 32
#define PROCESS_STACK_BASE 0x80000000
#define PROCESS_STACK_SIZE 0x4000
#define PROCESS_STACK_TOP (PROCESS_STACK_BASE + PROCESS_STACK_SIZE)
#define HEAP_BASE 0x80005000

#include "../Memory/Emalloc.h"
#include "../Memory/pmm.h"
#include "../Terminal/terminal.h"
#include "scheduler.h"
#include "../Memory/paging.h"
#include "../IO/io.h"
#include "../kernel.h"
#include "../Loader/elf.h"

typedef struct PCB{
    unsigned int k_esp;
    unsigned int esp;
    unsigned int eip;
    unsigned int pid;
    unsigned int stack_top;
    unsigned int stack_base;
    unsigned int wakeup_tick;
    unsigned int* PD;
    int state;
    unsigned int heap_start;
    unsigned int heap_end;
    struct Heap* heap;
    //void (*entry)(void);
} PCB;

extern unsigned int current_esp;
extern PCB process_table[MAX_PROCESS];
extern int process_count;
extern int current_process;

enum{
    P_FREE,
    P_NEW,
    P_READY,
    P_RUNNING,
    P_BLOCKED,
    P_TERMINATE
};

void process_init();
extern void process_save();
void process_switch();
void process_spawn(void (*entry)(void));
void update();
extern void switch_context(unsigned int new_process, unsigned int PD);
extern void load_cr3(unsigned int PD);

#endif