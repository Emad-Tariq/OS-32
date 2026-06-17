#include "paging.h"
#include "pmm.h"
#include "../Terminal/terminal.h"

unsigned int* PageDirectory;
unsigned int* PageTable;

void paging_init(){
    PageDirectory = (unsigned int*)pmm_alloc(1);
    PageTable = (unsigned int*)pmm_alloc(1);

    for(int i=0; i<1024; i++){
        PageTable[i] = (i * PAGE_SIZE) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_USER;
    }
    PageDirectory[0] = ((unsigned int)PageTable) | PAGE_PRESENT | PAGE_WRITABLE;
    for(int i = 1; i < 1024; i++){
        PageDirectory[i] = 0;
    }

    paging_enable(PageDirectory);
}