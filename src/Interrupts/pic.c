#include "pic.h"

void pic_init(){
    //ICW1, Start initialization
    outb(PIC1_Command, 0x11);
    outb(PIC2_Command, 0x11);

    //ICW2, set vector offsets
    outb(PIC1_Data, 0x20);
    outb(PIC2_Data, 0x28);

    //ICW3, tell master/slave about each other
    outb(PIC1_Data, 0x04); //Tell master that slave is at IRQ2
    outb(PIC2_Data, 0x02); //Cascade identity is 2

    //ICW4, set 8086 mode
    outb(PIC1_Data, 0x01);
    outb(PIC2_Data, 0x01);

    //mask all IRQs for now, unmask later as needed
    outb(PIC1_Data, 0xFF);
    outb(PIC2_Data, 0xFF);
}