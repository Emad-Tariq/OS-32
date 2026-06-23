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
    char* p = Emalloc(&process_table[current_process], 5000);

    for(int i=0; i<5000; i++)
        p[i] = 0xAA;

    for(int i=0; i<5000; i++)
    {
        if(p[i] != (char)0xAA)
            printf("CORRUPTION\n");
    }
    return;
}
void procB()
{
    char* p = Emalloc(&process_table[current_process], 100);
    return;
}
void idle(){
    while(1){
        
        update();
        asm volatile("hlt");
    }
}
void spawner(){
    while(1){
        for(int i=0; i<15; i++){
            process_spawn(&procA);
            process_spawn(&procB);
        }
        process_spawn(&procA);
        process_spawn(&procA);
        sleep(1);

        printf("free pages: %d\n", pmm_free_pages());
    }
}

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
    kernel_esp = (unsigned int)pmm_alloc(4) + 4*PAGE_SIZE;
    process_spawn(&spawner);
    process_spawn(&idle);
}

void kmain() {
    init();

    while(1);
}