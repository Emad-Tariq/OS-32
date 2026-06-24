#include "../Terminal/terminal.h"

volatile int x = 0;
volatile int y = 456;
char buffer[4096];
int main(){
    x = 1234;
    while(1);
}