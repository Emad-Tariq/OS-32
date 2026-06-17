#include "terminal.h"
#include "../IO/io.h"

int cursor; //global uninitialized because .bss zeroes and stores it safely, initializing it makes it inaccessible(still understanding why)
unsigned short* vga;

void update_cursor(){
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(cursor & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((cursor << 8) & 0xFF));
}

void terminal_init(){
    cursor = 0;
    vga = (unsigned short*)0xB8000;
    clear();
}

void backspace(){
    if(cursor <= 0) return;
    cursor--;
    putc(' ', cursor);
    update_cursor();
}

void type(char c){
    if(c == '\n') cursor += SCREEN_WIDTH - (cursor % SCREEN_WIDTH); //Put at start of next line
    else if(c == '\t') cursor += 4 - (cursor % 4); //Align to the next 4-gap space
    else{
        putc(c, cursor);
        cursor++;
    }

    if(cursor >= SCREEN_HEIGHT * SCREEN_WIDTH){
        clear();
        cursor = 0;
        update_cursor();
    }

    update_cursor();
}

void clear(){
    for (int i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
        vga[i] = (WHITE << 8) | ' ';
    }
    update_cursor();
}

void putc(char c, int pos){
    vga[pos] = (WHITE << 8) | (unsigned char)c;
}

void print(char* s){
    clear();
    for(int i=0; s[i] != '\0'; i++){
        putc(s[i], i);
    }
}

void printint(int n){
    if(n == 0) {type('0'); return;}
    if(n < 0) {type('-'); n = -n;}

    char buf[32];
    int i=0;

    while(n != 0){
        buf[i++] = n%10 + '0';
        n /= 10;
    }

    for(int j=i-1; j>=0; j--){
        type(buf[j]);
    }
}

void printhex(unsigned int n){
    type('0');
    type('x');
    
    if(n == 0) {type('0'); return;}
    if(n < 0) {type('-'); n = -n;}

    char buf[32];
    int i=0;

    while(n != 0){
        buf[i++] = n%16 >= 10 ? n%16 - 10 + 'A' : n%16 + '0';
        n /= 16;
    }

    for(int j=i-1; j>=0; j--){
        type(buf[j]);
    }
}

void printf(const char* fmt, ...){
    va_list args;
    va_start(args, fmt);
    for(int i=0; fmt[i] != '\0'; i++){
        if(fmt[i] == '%'){
            i++;
            if(fmt[i] == 'd'){
                int n = va_args(args, int);
                printint(n);
            }
            else if(fmt[i] == 's'){
                char* s = va_args(args, char*);
                for(int i=0; s[i] != '\0'; i++){
                    type(s[i]);
                }
            }
            else if(fmt[i] == 'c'){
                char c = va_args(args, int);
                type(c);
            }
            else if(fmt[i] == 'x'){
                unsigned int n = va_args(args, unsigned int);
                printhex(n);
            }
        } else {
            type(fmt[i]);
        }
    }

    va_end(args);
}