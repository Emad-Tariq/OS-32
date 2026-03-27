[BITS 16]
[ORG 0x7c00]


CODE_OFFSET equ 0x8
DATA_OFFSET equ 0x10

KERNEL_LOAD_SEG equ 0x1000
KERNEL_START_ADDR equ 0x10000



start:
    cli
    mov ax, 0xB800
    mov es, ax

    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00

;Load kernel
; mov bx, KERNEL_LOAD_SEG
mov ax, KERNEL_LOAD_SEG
mov es, ax
xor bx, bx
mov dh, 0x00
mov dl, 0x80
mov cl, 0x02
mov ch, 0x00
mov ah, 0x02
mov al, 8
int 0x13

jc disk_read_error


load_PM:
    cli
    in al, 0x92
    or al, 2
    out 0x92, al

    lgdt[gdt_descriptor]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    jmp CODE_OFFSET:PModeMain


disk_read_error:
    hlt

;GDT Implemetation

gdt_start:
    dd 0x0
    dd 0x0

    ; Code segment
    dw 0xFFFF       ; Limit
    dw 0x0000       ; Base
    db 0x00         ; Base
    db 10011010b    ; Access byte
    db 11001111b    ; Flags
    db 0x00         ; Base

    ; Data segment
    dw 0xFFFF       ; Limit
    dw 0x0000       ; Base
    db 0x00         ; Base
    db 10010010b    ; Access byte
    db 11001111b    ; Flags
    db 0x00         ; Base

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Size of GDT -1
    dd gdt_start               ; Addr of GDT


[BITS 32]
PModeMain:
    mov ax, DATA_OFFSET
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov ss, ax
    mov gs, ax
    mov ebp, 0x9C00
    mov esp, ebp

    jmp CODE_OFFSET:KERNEL_START_ADDR




times 510 - ($ - $$) db 0 

dw 0xAA55
