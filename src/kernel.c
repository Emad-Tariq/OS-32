#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"
#include "Interrupts/irq.h"
#include "Memory/pmm.h"
#include "Memory/Emalloc.h"
#include "Memory/paging.h"

void init(){
    idt_init();
    pic_init();
    scancode_init();
    terminal_init();
    pmm_init();
    Emalloc_init();
    paging_init();
    outb(0x21, 0xFD); //Unmask keyboard interrupts, 0xFD = 1111 1101 (bit 1 is unmasked)
    sti();
}

void kmain() {
    init();
    while(1);
}