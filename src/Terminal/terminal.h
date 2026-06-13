#ifndef TERMINAL_H
#define TERMINAL_H

#define WHITE 0x0F
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

typedef char* va_list;

#define va_start(ap, last) (ap = (char*)&last + sizeof(last))
#define va_args(ap, type) (*(type*)((ap += sizeof(type)) - sizeof(type)))
#define va_end(ap) (ap = 0)

void terminal_init();
void backspace();
void type(char c);
void clear();
void putc(char c, int pos);
void print(char* s);
void printint(int n);
void printhex(int n);
void printf(const char* fmt, ...);


#endif
