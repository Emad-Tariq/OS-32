#include "syscall.h"

void syscall_handler(){
    Registers* regs = (Registers* )(current_esp);

    switch (regs->eax)
    {
    case SYS_EXIT:
        process_kill();
        break;

    case SYS_SLEEP:
        process_sleep(regs->ebx);
        break;

    case SYS_WRITE:
        printf("%s", (char*)regs->ebx);
        break;

    case SYS_YIELD:
        process_save();
        process_switch();
        break;
    
    case SYS_SPAWN:
        process_spawn((char*)regs->ebx);
        break;
    }
}