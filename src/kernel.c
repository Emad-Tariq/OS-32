#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"
#include "Interrupts/irq.h"

void kmain() {
    idt_init();
    pic_init();
    scancode_init();
    terminal_init();
    outb(0x21, 0xFD); //Unmask keyboard interrupts, 0xFD = 1111 1101 (bit 1 is unmasked)
    sti();
    printf("Finally, formatted strings: %d\n", 50);
    printf("Testing string: %s", "my names skylar white yo \nmy husband's walter white, yo, uhuh\n");
    while(1);
}