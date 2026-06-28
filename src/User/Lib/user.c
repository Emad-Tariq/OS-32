#include "user.h"
#include "../../Syscalls/syscall.h"

void exit(){
    asm volatile(
        "mov %0, %%eax\n"
        "int $0x80"
        :
        : "i"(SYS_EXIT)
        : "eax"
    );
}
void yield(){
    asm volatile(
        "mov %0, %%eax\n"
        "int $0x80"
        :
        : "i"(SYS_YIELD)
        : "eax"
    );
}
void write(const char* str){
    asm volatile(
        "mov %0, %%eax\n"
        "mov %1, %%ebx\n"
        "int $0x80"
        :
        : "i"(SYS_WRITE), "r"(str)
        : "eax", "ebx"
    );
}

void sleep(unsigned int ticks){
    asm volatile(
        "mov %0, %%eax\n"
        "mov %1, %%ebx\n"
        "int $0x80"
        :
        : "i"(SYS_SLEEP), "r"(ticks)
        : "eax", "ebx"
    );
}

int spawn(const char* filename){
    int pid;
    asm volatile(
        "mov %1, %%eax\n"
        "mov %2, %%ebx\n"
        "int $0x80\n"
        "mov %%eax, %0"
        : "=r"(pid)
        : "i"(SYS_SPAWN), "r"(filename)
        : "eax", "ebx"
    );

    return pid;
}