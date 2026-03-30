#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"

void kmain() {
    clear();
    idt_init();
    print("Hello guys and welcome to my minecraft let's play video!!!!");
    int x = 0;
    int y = 1 / x;
    while(1);
}