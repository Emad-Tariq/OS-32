#ifndef PIC_H
#define PIC_H

#include "../IO/io.h"

#define PIC1_Command 0x20
#define PIC1_Data 0x21
#define PIC2_Command 0xA0
#define PIC2_Data 0xA1

void pic_init();

#endif 