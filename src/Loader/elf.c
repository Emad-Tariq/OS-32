#include "elf.h"
#include "../Process/process.h"

int load_elf(void* image, PCB* proc){
    Elf32_Ehdr* Ehdr = (Elf32_Ehdr*)image;
    if(Ehdr->e_ident[0] != 0x7F || 
        Ehdr->e_ident[1] != 'E' || 
        Ehdr->e_ident[2] != 'L' || 
        Ehdr->e_ident[3] != 'F' || 
        Ehdr->e_ident[4] != 1   ||
        Ehdr->e_ident[5] != 1   ||
        Ehdr->e_machine  != 3
    ){
        printf("Invalid ELF\n");
        return -1;
    }

    Elf32_Phdr* Phdr = (Elf32_Phdr*)((unsigned int)Ehdr + Ehdr->e_phoff);

    for(int i=0; i<Ehdr->e_phnum; i++){
        if(Phdr[i].p_type != PT_LOAD) continue;

        unsigned int pages = (Phdr[i].p_memsz + PAGE_SIZE - 1)/PAGE_SIZE;
        unsigned int addr = Phdr[i].p_vaddr;
        for(int j=0; j<pages; j++){
            unsigned int phy = (unsigned int)pmm_alloc(1);
            map_page(proc->PD, addr, phy, PAGE_PRESENT | PAGE_WRITABLE);
            addr += PAGE_SIZE;
        }

        unsigned int old_cr3;
        asm volatile(
            "mov %%cr3, %0"
            : "=r"(old_cr3)
        );
        asm volatile(
            "mov %0, %%cr3"
            :
            : "r"(proc->PD)
            : "memory"
        );
        memcpy(
            (void*)Phdr[i].p_vaddr,
            (char*)image + Phdr[i].p_offset,
            Phdr[i].p_filesz
        );

        memset(
            (void*)(Phdr[i].p_vaddr + Phdr[i].p_filesz),
            0,
            Phdr[i].p_memsz - Phdr[i].p_filesz
        );

        asm volatile(
            "mov %0, %%cr3"
            :
            : "r"(old_cr3)
            : "memory"
        );
    }

    proc->e_entry = Ehdr->e_entry;
    return 0;
}