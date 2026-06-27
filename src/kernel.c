#include "kernel.h"

void init(){
    terminal_init();
    idt_init();
    pic_init();
    scancode_init();
    pmm_init();
    paging_init();
    process_init();
    outb(0x21, 0xFC); //Unmask keyboard interrupts and timer, 0xFC = 1111 1100 (bit 0 and 1 is unmasked)
    scheduler_init();
    fs_init();

    kernel_esp = (unsigned int)pmm_alloc(4) + 4*PAGE_SIZE;
    process_spawn("idle.elf");
    process_spawn("hello.elf");
}

void kmain() {
    init();
    sti();

    while(1);
}