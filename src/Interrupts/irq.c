#include "../IO/io.h"
#include "../Terminal/terminal.h"
#include "../Process/process.h"
#include "../Process/scheduler.h"
#include "irq.h"

char scancode_table[128];  // uninitialized global — safe, lives in .bss
char scancode_shift_table[128];
int shift;

void scancode_init() {
    scancode_table[0x02] = '1';
    scancode_table[0x03] = '2';
    scancode_table[0x04] = '3';
    scancode_table[0x05] = '4';
    scancode_table[0x06] = '5';
    scancode_table[0x07] = '6';
    scancode_table[0x08] = '7';
    scancode_table[0x09] = '8';
    scancode_table[0x0A] = '9';
    scancode_table[0x0B] = '0';
    scancode_table[0x0C] = '-';
    scancode_table[0x0D] = '=';
    scancode_table[0x0E] = 0;    // backspace
    scancode_table[0x0F] = '\t';
    scancode_table[0x10] = 'q';
    scancode_table[0x11] = 'w';
    scancode_table[0x12] = 'e';
    scancode_table[0x13] = 'r';
    scancode_table[0x14] = 't';
    scancode_table[0x15] = 'y';
    scancode_table[0x16] = 'u';
    scancode_table[0x17] = 'i';
    scancode_table[0x18] = 'o';
    scancode_table[0x19] = 'p';
    scancode_table[0x1A] = '[';
    scancode_table[0x1B] = ']';
    scancode_table[0x1C] = '\n';
    scancode_table[0x1D] = 0;    // ctrl
    scancode_table[0x1E] = 'a';
    scancode_table[0x1F] = 's';
    scancode_table[0x20] = 'd';
    scancode_table[0x21] = 'f';
    scancode_table[0x22] = 'g';
    scancode_table[0x23] = 'h';
    scancode_table[0x24] = 'j';
    scancode_table[0x25] = 'k';
    scancode_table[0x26] = 'l';
    scancode_table[0x27] = ';';
    scancode_table[0x28] = '\'';
    scancode_table[0x29] = '`';
    scancode_table[0x2A] = 0;    // left shift
    scancode_table[0x2B] = '\\';
    scancode_table[0x2C] = 'z';
    scancode_table[0x2D] = 'x';
    scancode_table[0x2E] = 'c';
    scancode_table[0x2F] = 'v';
    scancode_table[0x30] = 'b';
    scancode_table[0x31] = 'n';
    scancode_table[0x32] = 'm';
    scancode_table[0x33] = ',';
    scancode_table[0x34] = '.';
    scancode_table[0x35] = '/';
    scancode_table[0x36] = 0;    // right shift
    scancode_table[0x37] = '*';
    scancode_table[0x38] = 0;    // alt
    scancode_table[0x39] = ' ';

    scancode_shift_table[0x02] = '!';
    scancode_shift_table[0x03] = '@';
    scancode_shift_table[0x04] = '#';
    scancode_shift_table[0x05] = '$';
    scancode_shift_table[0x06] = '%';
    scancode_shift_table[0x07] = '^';
    scancode_shift_table[0x08] = '&';
    scancode_shift_table[0x09] = '*';
    scancode_shift_table[0x0A] = '(';
    scancode_shift_table[0x0B] = ')';
    scancode_shift_table[0x0C] = '_';
    scancode_shift_table[0x0D] = '+';

    // shifted letters (uppercase)
    scancode_shift_table[0x10] = 'Q';
    scancode_shift_table[0x11] = 'W';
    scancode_shift_table[0x12] = 'E';
    scancode_shift_table[0x13] = 'R';
    scancode_shift_table[0x14] = 'T';
    scancode_shift_table[0x15] = 'Y';
    scancode_shift_table[0x16] = 'U';
    scancode_shift_table[0x17] = 'I';
    scancode_shift_table[0x18] = 'O';
    scancode_shift_table[0x19] = 'P';
    scancode_shift_table[0x1A] = '{';
    scancode_shift_table[0x1B] = '}';
    scancode_shift_table[0x1E] = 'A';
    scancode_shift_table[0x1F] = 'S';
    scancode_shift_table[0x20] = 'D';
    scancode_shift_table[0x21] = 'F';
    scancode_shift_table[0x22] = 'G';
    scancode_shift_table[0x23] = 'H';
    scancode_shift_table[0x24] = 'J';
    scancode_shift_table[0x25] = 'K';
    scancode_shift_table[0x26] = 'L';
    scancode_shift_table[0x27] = ':';
    scancode_shift_table[0x28] = '"';
    scancode_shift_table[0x29] = '~';
    scancode_shift_table[0x2B] = '|';
    scancode_shift_table[0x2C] = 'Z';
    scancode_shift_table[0x2D] = 'X';
    scancode_shift_table[0x2E] = 'C';
    scancode_shift_table[0x2F] = 'V';
    scancode_shift_table[0x30] = 'B';
    scancode_shift_table[0x31] = 'N';
    scancode_shift_table[0x32] = 'M';
    scancode_shift_table[0x33] = '<';
    scancode_shift_table[0x34] = '>';
    scancode_shift_table[0x35] = '?';
    scancode_shift_table[0x39] = ' ';
    shift = 0;
}

void send_eoi(int irq){
    if(irq >= 8) outb(0xA0, PIC_EOI);
    outb(0x20, PIC_EOI);
}

void irq0_handler(){
    system_ticks++;
    send_eoi(0);
    process_switch();
}

void irq1_handler(){
    //Keyboard interrupt
    unsigned char scancode = inb(0x60);
    if(scancode & 0x80){
        if(scancode == 0xAA || scancode == 0xB6) shift = 0;
        send_eoi(1);
        return;
    }

    if(scancode == 0x0E){
        backspace();
        send_eoi(1);
        return;
    }
    if((scancode == 0x2A || scancode == 0x36)) shift = 1;

    char c = shift ? scancode_shift_table[scancode] : scancode_table[scancode];
    if(c != 0) type(c);
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
