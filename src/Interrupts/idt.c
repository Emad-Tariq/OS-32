#include "idt.h"

IDTEntry idt[256];
IDTPointer idtr;

extern void idt_load(IDTPointer* idtr);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void idt_init(){
    idt_set_entry(0, (unsigned int)isr0);
    idt_set_entry(1, (unsigned int)isr1);
    idt_set_entry(2, (unsigned int)isr2);
    idt_set_entry(3, (unsigned int)isr3);
    idt_set_entry(4, (unsigned int)isr4);
    idt_set_entry(5, (unsigned int)isr5);
    idt_set_entry(6, (unsigned int)isr6);
    idt_set_entry(7, (unsigned int)isr7);
    idt_set_entry(8, (unsigned int)isr8);
    idt_set_entry(9, (unsigned int)isr9);
    idt_set_entry(10, (unsigned int)isr10);
    idt_set_entry(11, (unsigned int)isr11);
    idt_set_entry(12, (unsigned int)isr12);
    idt_set_entry(13, (unsigned int)isr13);
    idt_set_entry(14, (unsigned int)isr14);
    idt_set_entry(15, (unsigned int)isr15);
    idt_set_entry(16, (unsigned int)isr16);
    idt_set_entry(17, (unsigned int)isr17);
    idt_set_entry(18, (unsigned int)isr18);
    idt_set_entry(19, (unsigned int)isr19);
    idt_set_entry(20, (unsigned int)isr20);
    idt_set_entry(21, (unsigned int)isr21);
    idt_set_entry(22, (unsigned int)isr22);
    idt_set_entry(23, (unsigned int)isr23);
    idt_set_entry(24, (unsigned int)isr24);
    idt_set_entry(25, (unsigned int)isr25);
    idt_set_entry(26, (unsigned int)isr26);
    idt_set_entry(27, (unsigned int)isr27);
    idt_set_entry(28, (unsigned int)isr28);
    idt_set_entry(29, (unsigned int)isr29);
    idt_set_entry(30, (unsigned int)isr30);
    idt_set_entry(31, (unsigned int)isr31);
    idtr.limit = (sizeof(IDTEntry) * 256) - 1;
    idtr.base  = (unsigned int)&idt;

    idt_load(&idtr);
}

void idt_set_entry(int n, unsigned int handler){
    idt[n].offset_low  = handler & 0xFFFF;
    idt[n].selector    = 0x08; 
    idt[n].zero        = 0;
    idt[n].type_attr   = 0x8E;
    idt[n].offset_high = (handler >> 16) & 0xFFFF;

}