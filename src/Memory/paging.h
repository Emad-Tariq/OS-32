#ifndef PAGING_H
#define PAGING_H

#define PAGE_PRESENT  0x1
#define PAGE_WRITABLE 0x2
#define PAGE_USER     0x4

#include "pmm.h"
#include "../Terminal/terminal.h"

extern unsigned int* kernel_pd;

void paging_init();
unsigned int* create_page_directory();
void map_page(unsigned int* pagedirectory, unsigned int virt, unsigned int phy, unsigned int EFLAGS);
void unmap_page(unsigned int* pagedirectory, unsigned int virt);
unsigned int get_phy_addr(unsigned int* pagedirectory, unsigned int virt);
extern void paging_enable(unsigned int* PageDirectory);
extern void tlb_flush();

#endif