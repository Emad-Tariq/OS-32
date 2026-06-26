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
global outw
outw:
    mov dx, [esp + 4]
    mov ax, [esp + 8]
    out dx, ax
    ret
global inw
inw:
    xor eax, eax
    mov dx, [esp + 4]
    in ax, dx
    ret
global outl
outl:
    mov dx, [esp + 4]
    mov eax, [esp + 8]
    out dx, eax
    ret
global inl
inl:
    mov dx, [esp + 4]
    in eax, dx
    ret

global sti 
global cli
sti:
    sti
    ret
cli:
    cli
    ret