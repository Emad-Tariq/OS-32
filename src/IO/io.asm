[BITS 32]
global outb 
outb:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al 
    ret 

global inb 
inb:
    xor eax, eax
    mov dx, [esp + 4]
    in al, dx
    ret

global sti 
sti:
    sti
    ret