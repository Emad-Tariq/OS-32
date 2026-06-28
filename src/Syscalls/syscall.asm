[BITS 32]
global syscall
extern syscall_handler
extern kernel_esp
extern current_esp

syscall:
    cli
    pusha

    mov [current_esp], esp
    mov esp, [kernel_esp]

    call syscall_handler

    mov esp, [current_esp]

    sti
    popa
    iret 