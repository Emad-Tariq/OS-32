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

    static unsigned char elf_buff[64 * 1024];
    ata_read(69, elf_buff, 9);
    kernel_esp = (unsigned int)pmm_alloc(4) + 4*PAGE_SIZE;
    process_spawn((void*)elf_buff);
}

void kmain() {
    init();
    //sti();

    while(1);
}