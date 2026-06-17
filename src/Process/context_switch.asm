global switch_context
switch_context:
    mov eax, [esp+4]
    mov esp, eax
    popa
    iret
