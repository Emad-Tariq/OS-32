#ifndef SYSCALL_H
#define SYSCALL_H

#include "../kernel.h"

enum{
    SYS_EXIT,
    SYS_WRITE,
    SYS_SPAWN,
    SYS_SLEEP,
    SYS_YIELD
};

typedef struct Registers {
    unsigned int edi;
    unsigned int esi;
    unsigned int ebp;
    unsigned int esp;   // original ESP before pusha
    unsigned int ebx;
    unsigned int edx;
    unsigned int ecx;
    unsigned int eax;
} Registers;

void syscall_handler();

#endif