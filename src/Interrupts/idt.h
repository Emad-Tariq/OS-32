#ifndef IDT_H
#define IDT_H

typedef struct {
    unsigned short offset_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short offset_high;
} __attribute__((packed)) IDTEntry;

typedef struct {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed)) IDTPointer;

void idt_init();
void idt_set_entry(int n, unsigned int handler);



#endif