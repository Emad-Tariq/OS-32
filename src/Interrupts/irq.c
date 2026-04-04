#include "../IO/io.h"
#include "../Terminal/terminal.h"

void send_eoi(int irq){
    if(irq >= 8) outb(0xA0, PIC_EOI);
    outb(0x20, PIC_EOI);
}

void irq0_handler(){
    //Timer interrupt
    print("TIMER INTERRUPT");
    send_eoi(0);
}

void irq1_handler(){
    //Keyboard interrupt
    unsigned char scancode = inb(0x60);
    print(&scancode);
    send_eoi(1);
}

void irq2_handler() {send_eoi(2);}
void irq3_handler() {send_eoi(3);}
void irq4_handler() {send_eoi(4);}
void irq5_handler() {send_eoi(5);}
void irq6_handler() {send_eoi(6);}
void irq7_handler() {send_eoi(7);}
void irq8_handler() {send_eoi(8);}
void irq9_handler() {send_eoi(9);}
void irq10_handler() {send_eoi(10);}
void irq11_handler() {send_eoi(11);}
void irq12_handler() {send_eoi(12);}
void irq13_handler() {send_eoi(13);}
void irq14_handler() {send_eoi(14);}
void irq15_handler() {send_eoi(15);}
