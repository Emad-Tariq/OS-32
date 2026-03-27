[BITS 32]
global idt_load
extern isr0_handler
extern isr1_handler
extern isr2_handler
extern isr3_handler
extern isr4_handler
extern isr5_handler
extern isr6_handler
extern isr7_handler
extern isr8_handler
extern isr9_handler
extern isr10_handler
extern isr11_handler
extern isr12_handler
extern isr13_handler
extern isr14_handler
extern isr15_handler
extern isr16_handler
extern isr17_handler
extern isr18_handler
extern isr19_handler
extern isr20_handler
extern isr21_handler
extern isr22_handler
extern isr23_handler
extern isr24_handler
extern isr25_handler
extern isr26_handler
extern isr27_handler
extern isr28_handler
extern isr29_handler
extern isr30_handler
extern isr31_handler

global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

idt_load:
    mov eax, [esp+4]
    lidt [eax]
    ret

isr0:
    pusha
    call isr0_handler
    popa
    iret
isr1:
    pusha
    call isr1_handler
    popa
    iret
isr2:
    pusha
    call isr2_handler
    popa
    iret
isr3:
    pusha
    call isr3_handler
    popa
    iret
isr4:
    pusha
    call isr4_handler
    popa
    iret
isr5:
    pusha
    call isr5_handler
    popa
    iret
isr6:
    pusha
    call isr6_handler
    popa
    iret
isr7:
    pusha
    call isr7_handler
    popa
    iret
isr8:
    pusha
    call isr8_handler
    popa
    iret
isr9:
    pusha
    call isr9_handler
    popa
    iret
isr10:
    pusha
    call isr10_handler
    popa
    iret
isr11:
    pusha
    call isr11_handler
    popa
    iret
isr12:
    pusha
    call isr12_handler
    popa
    iret
isr13:
    pusha
    call isr13_handler
    popa
    iret
isr14:
    pusha
    call isr14_handler
    popa
    iret
isr15:
    pusha
    call isr15_handler
    popa
    iret
isr16:
    pusha
    call isr16_handler
    popa
    iret
isr17:
    pusha
    call isr17_handler
    popa
    iret
isr18:
    pusha
    call isr18_handler
    popa
    iret
isr19:
    pusha
    call isr19_handler
    popa
    iret
isr20:
    pusha
    call isr20_handler
    popa
    iret
isr21:
    pusha
    call isr21_handler
    popa
    iret
isr22:
    pusha
    call isr22_handler
    popa
    iret
isr23:
    pusha
    call isr23_handler
    popa
    iret
isr24:
    pusha
    call isr24_handler
    popa
    iret
isr25:
    pusha
    call isr25_handler
    popa
    iret
isr26:
    pusha
    call isr26_handler
    popa
    iret
isr27:
    pusha
    call isr27_handler
    popa
    iret
isr28:
    pusha
    call isr28_handler
    popa
    iret
isr29:
    pusha
    call isr29_handler
    popa
    iret
isr30:
    pusha
    call isr30_handler
    popa
    iret
isr31:
    pusha
    call isr31_handler
    popa
    iret
