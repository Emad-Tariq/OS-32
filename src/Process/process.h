#ifndef PROCESS_H
#define PROCESS_H

#define MAX_PROCESS 32

extern unsigned int current_esp;

enum{
    P_FREE,
    P_READY,
    P_RUNNING,
};

// typedef struct{
//     unsigned int esp;
//     unsigned int ebp;
//     unsigned int eip;
//     unsigned int cr3;

//     // general purpose registers
//     unsigned int eax;
//     unsigned int ebx;
//     unsigned int ecx;
//     unsigned int edx;
// } Process;

typedef struct{
    unsigned int esp;
    unsigned int pid;
    int state;
} PCB;

void process_init();
void process_switch();
void process_spawn(void (*entry)(void));
extern void switch_context(unsigned int new_process);

#endif