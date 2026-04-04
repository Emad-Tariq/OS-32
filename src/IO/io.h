#ifndef IO_H
#define IO_H

#define PIC_EOI 0x20
void outb(unsigned short port, unsigned char value);
unsigned char inb(unsigned short port);
void sti();




#endif