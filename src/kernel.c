#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"
#include "Interrupts/irq.h"
#include "Memory/pmm.h"
#include "Memory/Emalloc.h"

void kmain() {
    idt_init();
    pic_init();
    scancode_init();
    terminal_init();
    pmm_init();
    Emalloc_init();
    outb(0x21, 0xFD); //Unmask keyboard interrupts, 0xFD = 1111 1101 (bit 1 is unmasked)
    sti();


    void* a = Emalloc(50);
    void* b = Emalloc(100);
    void* c = Emalloc(200);

    printf("a: %x\n", (unsigned int)a);
    printf("b: %x\n", (unsigned int)b);
    printf("c: %x\n", (unsigned int)c);

    Efree(b);

    void* d = Emalloc(100);  // should reuse b's block
    printf("d: %x\n", (unsigned int)d);  // should equal b
    while(1);
}