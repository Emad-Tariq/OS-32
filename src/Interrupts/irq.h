#ifndef IRQ_H
#define IRQ_H
#include "../IO/io.h"

void scancode_init();
void send_eoi(int irq);

#endif