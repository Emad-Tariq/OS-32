#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"

void kmain() {
    clear();
    idt_init();
    pic_init();
    outb(0x21, 0xFD); //Unmask keyboard interrupts, 0xFD = 1111 1101 (bit 1 is unmasked)
    sti();
    print("Hello guys and welcome to my minecraft let's play video!!!!");
    while(1);
}