#include "Emalloc.h"

void Emalloc_init(PCB* proc){
    void* phy = pmm_alloc(1);
    map_page(proc->PD, HEAP_BASE, (unsigned int)phy, PAGE_PRESENT | PAGE_WRITABLE);

    proc->heap = (Heap*)HEAP_BASE;
    proc->heap_end += PAGE_SIZE;

    Heap* init_heap = (Heap*)phy;
    init_heap->free = 1;
    init_heap->next = 0;
    init_heap->size = PAGE_SIZE - sizeof(Heap);
}

void* Emalloc(PCB* proc, unsigned int bytes){
    Heap* iter = proc->heap;
    Heap* last;
    while(iter != 0){
        if(iter->size >= bytes && iter->free){
            if(iter->size > bytes + sizeof(Heap)){
                Heap* next_block = (Heap*)((char*)iter + sizeof(Heap) + bytes);
                next_block->free = 1;
                next_block->size = iter->size - bytes - sizeof(Heap);
                next_block->next = iter->next;

                iter->size = bytes;
                iter->free = 0;
                iter->next = next_block;
            } else{
                iter->free = 0;
            }

            return (void*)((char*)iter + sizeof(Heap));
        }
        last = iter;
        iter = iter->next;
    }

    unsigned int next_block_addr = proc->heap_end;
    unsigned int pages = (bytes + sizeof(Heap) + PAGE_SIZE - 1) / PAGE_SIZE;
    for(int i=0; i<pages; i++){
        void* phy = pmm_alloc(1);

        map_page(
            proc->PD,
            proc->heap_end,
            (unsigned int)phy,
            PAGE_PRESENT | PAGE_WRITABLE
        );
        proc->heap_end += PAGE_SIZE;
    }
    Heap* new_block = (Heap*)next_block_addr;
    new_block->free = 1;
    new_block->next = 0;
    new_block->size = pages * PAGE_SIZE - sizeof(Heap);
    last->next = new_block;

    return Emalloc(proc, bytes);
}

void Efree(PCB* proc, void* ptr){
    Heap* cur = (Heap*)((unsigned int)ptr - sizeof(Heap));
    cur->free = 1;

    Heap* iter = proc->heap;
    while(iter != 0 && iter->next != 0){
        if(iter->free && iter->next->free){
            iter->size += iter->next->size + (unsigned int)sizeof(Heap);
            iter->next = iter->next->next;
        } else {
        iter = iter->next;
        }
    }
}

void print_heap(PCB* proc){
    Heap* iter = proc->heap;
    int count = 0;
    while(iter != 0){
        printf("Block %d, Size: %d, Free: %d, Next: %x\n", count, iter->size, iter->free, (unsigned int)iter->next);
        count++;
        iter = iter->next;
    }
    printf("\n");
}