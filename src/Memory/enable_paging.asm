global paging_enable
paging_enable:
    mov eax, [esp+4]    ; page directory address
    mov cr3, eax        ; load into CR3
    mov eax, cr0
    or  eax, 0x80000000 ; set bit 31
    mov cr0, eax        ; enable paging
    ret