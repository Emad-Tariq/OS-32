#include "../Terminal/terminal.h"

void isr0_handler()  { print("Exception: Division By Zero"); while(1);}
void isr1_handler()  { print("Exception: Debug"); }
void isr2_handler()  { print("Exception: NMI"); }
void isr3_handler()  { print("Exception: Breakpoint"); }
void isr4_handler()  { print("Exception: Overflow"); }
void isr5_handler()  { print("Exception: Bound Range Exceeded"); }
void isr6_handler()  { print("Exception: Invalid Opcode"); }
void isr7_handler()  { print("Exception: Device Not Available"); }
void isr8_handler()  { print("Exception: Double Fault"); }
void isr9_handler()  { print("Exception: Coprocessor Segment Overrun"); }
void isr10_handler() { print("Exception: Invalid TSS"); }
void isr11_handler() { print("Exception: Segment Not Present"); }
void isr12_handler() { print("Exception: Stack Segment Fault"); }
void isr13_handler() { print("Exception: General Protection Fault"); }
void isr14_handler() { print("Exception: Page Fault"); }
void isr15_handler() { print("Exception: Reserved"); }
void isr16_handler() { print("Exception: FPU Exception"); }
void isr17_handler() { print("Exception: Alignment Check"); }
void isr18_handler() { print("Exception: Machine Check"); }
void isr19_handler() { print("Exception: SIMD Exception"); }
void isr20_handler() { print("Exception: Virtualization Exception"); }
void isr21_handler() { print("Exception: Control Protection Exception"); }
void isr22_handler() { print("Exception: Reserved"); }
void isr23_handler() { print("Exception: Reserved"); }
void isr24_handler() { print("Exception: Reserved"); }
void isr25_handler() { print("Exception: Reserved"); }
void isr26_handler() { print("Exception: Reserved"); }
void isr27_handler() { print("Exception: Reserved"); }
void isr28_handler() { print("Exception: Hypervisor Injection Exception"); }
void isr29_handler() { print("Exception: VMM Communication Exception"); }
void isr30_handler() { print("Exception: Security Exception"); }
void isr31_handler() { print("Exception: Reserved"); }