[BITS 32]
global switch_context
switch_context:
    mov eax, [esp+4]
    mov ecx, [esp+8]
    mov cr3, ecx
    mov esp, eax
    popa
    iret

