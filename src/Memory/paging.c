#include "paging.h"

unsigned int* kernelPD;

void paging_init(){
    kernelPD = (unsigned int*)pmm_alloc(1);
    for(int i=0; i<1024; i++){
        unsigned int* kernelPT = (unsigned int*)pmm_alloc(1);
        for(int j=0; j<1024; j++){
            kernelPT[j] = ((i * 1024 + j) * PAGE_SIZE) | PAGE_PRESENT | PAGE_WRITABLE | PAGE_USER;
        }
        kernelPD[i] = ((unsigned int)kernelPT) | PAGE_PRESENT | PAGE_WRITABLE;
    }

    paging_enable(kernelPD);
}

unsigned int* create_page_directory(){
    unsigned int* newPD = (unsigned int*)pmm_alloc(1);
    for(int i=0; i<1024; i++){
        if (i < 512) {
            newPD[i] = kernelPD[i];
        } else {
            newPD[i] = 0;
        }
    }
    
    return newPD;
}

void map_page(unsigned int* pagedirectory, unsigned int virt, unsigned int phy, unsigned int EFLAGS){
    unsigned int PD_idx = (virt >> 22) & 0x3FF;
    unsigned int PT_idx = (virt >> 12) & 0x3FF;

    unsigned int* pagetable;
    if(!(pagedirectory[PD_idx] & PAGE_PRESENT)){
        pagetable = pmm_alloc(1);
        for(int i=0; i<1024; i++){
            pagetable[i] = 0;
        }

        pagedirectory[PD_idx] = (((unsigned int)pagetable) | PAGE_PRESENT | PAGE_WRITABLE);
    }
    else{
        pagetable = (unsigned int*)(pagedirectory[PD_idx] & 0xFFFFF000);
    }

    pagetable[PT_idx] = phy | EFLAGS;
    tlb_flush();
}

void unmap_page(unsigned int* pagedirectory, unsigned int virt){
    unsigned int PD_idx = (virt >> 22) & 0x3FF;
    unsigned int PT_idx = (virt >> 12) & 0x3FF;

    unsigned int* pagetable;
    if(!(pagedirectory[PD_idx] & PAGE_PRESENT)) return;
    pagetable = (unsigned int*)(pagedirectory[PD_idx] & 0xFFFFF000);
    pagetable[PT_idx] = 0;

    int empty = 1;
    for(int i=0; i<1024; i++){
        if(pagetable[i] & PAGE_PRESENT){
            empty = 0;
            break;
        }
    }

    if(empty){
        pmm_free((unsigned int)pagetable, 1);
        pagedirectory[PD_idx] = 0;
    }
    tlb_flush();
}

unsigned int get_phy_addr(unsigned int* pagedirectory, unsigned int virt){
    unsigned int PD_idx = (virt >> 22) & 0x3FF;
    unsigned int PT_idx = (virt >> 12) & 0x3FF;

    unsigned int* pagetable;
    if(!(pagedirectory[PD_idx] & PAGE_PRESENT)) return 0;

    pagetable = (unsigned int*)(pagedirectory[PD_idx] & 0xFFFFF000);

    if(!(pagetable[PT_idx] & PAGE_PRESENT)) return 0;
    return pagetable[PT_idx] & 0xFFFFF000;
}