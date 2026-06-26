#include "../Terminal/terminal.h"

volatile int x = 0;
volatile int y = 456;
char buffer[4096];
int main(){
    x = 1234;
    buffer[4095] = 'a';
    //*((unsigned int*)0xFFFFFFFF) = 0;
    while(1);
}