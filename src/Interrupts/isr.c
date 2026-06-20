#include "../Terminal/terminal.h"
#include "../Memory/paging.h"
#include "../Process/process.h"

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
void isr12_handler() {
    printf("STACK FAULT\n");
    //for(int i=0; i<1000000000; i++){}
    while(1);
}
void isr13_handler() {
    printf("GPF\n");
    //for(int i=0; i<1000000000; i++){}
    while(1);
}

void isr14_handler() {
    if(current_process >= 0){
        unsigned int fault_addr;
        asm volatile(
            "mov %%cr2, %0"
            : "=r"(fault_addr)
        );
        printf("Exception: Page Fault at %x\n", fault_addr);
        printf("esp: %x\n", process_table[current_process].esp);
        fault_addr &= 0xFFFFF000;
        //for(int i=0; i<1000000000; i++){}

        if(fault_addr >= process_table[current_process].stack_base && fault_addr < process_table[current_process].stack_top){
            void* page = pmm_alloc(1);
            map_page(process_table[current_process].PD, fault_addr, (unsigned int)page, PAGE_PRESENT | PAGE_WRITABLE);
            tlb_flush();
            return;
        }
        
        // printf("CR0 = %x\n", cr0);
        printf("Segmentation Fault");
    }
    while(1);
}


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