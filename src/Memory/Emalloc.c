#include "Emalloc.h"
#include "pmm.h"
#include "../Terminal/terminal.h"


Block* heap;

void Emalloc_init(){
    heap = (Block*)pmm_alloc(2560);
    if(heap) printf("HEAP ALLOCATED!!!\n");
    else return;

    heap->free = 1;
    heap->size = (HEAP_SIZE * PAGE_SIZE) - sizeof(Block);
    heap->next = 0;
}

void* Emalloc(unsigned int bytes){
    Block* iter = heap;
    while(iter != 0){
        if(iter->size >= bytes && iter->free){
            Block* next_block = (Block*)((char*)iter + sizeof(Block) + bytes);
            next_block->free = 1;
            next_block->size = iter->size - bytes - sizeof(Block);
            next_block->next = 0;

            iter->size = bytes;
            iter->free = 0;
            iter->next = next_block;

            return (void*)((char*)iter + sizeof(Block));
        }

        iter = iter->next;
    }

    printf("FATAL: Emalloc: out of heap memory\n");
    return 0;
}

void Efree(void* ptr){
    Block* cur = (Block*)((char*)ptr - sizeof(Block));
    cur->free = 1;

    Block* iter = heap;
    while(iter != 0 && iter->next != 0){
        if(iter->free && iter->next->free){
            iter->size += iter->next->size + (unsigned int)sizeof(Block);
            iter->next = iter->next->next;
        } else {
        iter = iter->next;
        }
    }
}