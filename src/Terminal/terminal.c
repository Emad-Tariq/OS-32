#include "terminal.h"

void clear(){
    unsigned short* vga = (unsigned short*)0xB8000;
    for (int i = 0; i < 80*25; i++) {
        vga[i] = (WHITE << 8) | ' ';
    }
}

void putc(char c, int pos){
    unsigned short* vga = (unsigned short*)0xB8000;
    vga[pos] = (WHITE << 8) | (unsigned char)c;
}

void print(char* s){
    clear();
    for(int i=0; s[i] != '\0'; i++){
        putc(s[i], i);
    }
}