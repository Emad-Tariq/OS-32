#include "kernel.h"

void kmain() {
    unsigned short *video = (unsigned short*)0xB8000;

    for (int i = 0; i < 80*25; i++) {
        video[i] = 0x0720;   // white 'A'
    }

    video[0] = 0x0F4F;
    video[1] = 0x0F4B;

    while(1);
}