#include "pmm.h"
#include "Terminal/terminal.h"

unsigned int *bitmap;
int free_pages;

void pmm_init(){
    MemMapEntry* PMM = (MemMapEntry*)0x504;
    unsigned short count = *(unsigned short*)0x500;
    bitmap = (unsigned int*)BITMAP_ADDR;
    // printf("CHECKING RAM\n");
    // printf("Segment count: %d\n", count);
    // for(int i=0; i<count; i++){
    //     printf("base: %x   length: %x   type: %d\n", (unsigned int)PMM[i].base, (unsigned int)PMM[i].length, PMM[i].type);
    // }

    for(int i=0; i<BITMAP_SIZE; i++){
        bitmap[i] = 0xFFFFFFFF;
    }

    for(int i=0; i<count; i++){
        if(PMM[i].type == 1){
            unsigned long long base = PMM[i].base;
            unsigned long long length = PMM[i].length;

            unsigned long long page_start = base / PAGE_SIZE;
            unsigned long long page_end = (base + length) / PAGE_SIZE;

            for(int page = page_start; page < page_end; page++){
                //bitmap[page / 32] &= ~(1 << (page % 32));
                pmm_clear(page);
            }
        }
    }

    unsigned int page_end = (BITMAP_ADDR  + 4 * BITMAP_SIZE) / PAGE_SIZE;
    for(int page = 0; page < page_end; page++){
        //bitmap[page / 32] |= (1 << (page % 32));
        pmm_set(page);
    }
    free_pages = MAX_PAGES;
}

void pmm_set(int page){
    bitmap[page / 32] |= (1 << (page % 32));
}
void pmm_clear(int page){
    bitmap[page / 32] &= ~(1 << (page % 32));
}
int pmm_test(int page){
    return bitmap[page / 32] & (1 << (page % 32));
}
void* pmm_alloc(unsigned int numpages){
    for(int page = 0; page < MAX_PAGES; page++){
        int free = 1;
        for(int i = 0; i < numpages; i++){
            if(pmm_test(i + page)){
                free = 0;
                break;
            }
        }

        if(free){
            for(unsigned int j = 0; j < numpages; j++){
                pmm_set(page + j);
            }
            free_pages -= numpages;
            return (void*)(page * PAGE_SIZE);
        }
    }

    printf("FATAL: pmm: Not enough memory\n");
}

void pmm_free(unsigned int address, unsigned int numpages){
    unsigned int page_num = address / PAGE_SIZE;
    for(int i=0; i<numpages; i++){
        pmm_clear(page_num + i);
    }
    free_pages += numpages;
}
unsigned int pmm_free_pages(){
    return free_pages;
}

unsigned int pmm_used_pages(){
    return MAX_PAGES - free_pages;
}