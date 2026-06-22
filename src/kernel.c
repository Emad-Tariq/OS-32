#include "kernel.h"
#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"
#include "Interrupts/irq.h"
#include "Memory/pmm.h"
#include "Memory/Emalloc.h"
#include "Memory/paging.h"
#include "Process/process.h"
#include "Process/scheduler.h"

void procA()
{
    //while(1) {printf("a"); sleep(5);}
    for(int i=0; i<1; i++) printf("A");
    return;
}
void procB()
{
    //while(1) printf("B");
    for(int i=0; i<1; i++) printf("B");
    return;
}
void idle(){
    while(1){
        
        update();
        asm volatile("hlt");
    }
}

void init(){
    terminal_init();
    idt_init();
    pic_init();
    scancode_init();
    pmm_init();
    Emalloc_init();
    paging_init();
    process_init();
    outb(0x21, 0xFC); //Unmask keyboard interrupts and timer, 0xFC = 1111 1100 (bit 0 and 1 is unmasked)
    scheduler_init();

    process_spawn(&idle);
    //sti();
}

void kmain() {
    init();
    //cli();
    for(int i=0; i<15; i++){
        process_spawn(&procA);
        process_spawn(&procB);
    }
    sti();

    while(1);
}