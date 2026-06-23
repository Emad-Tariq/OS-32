#ifndef EMALLOC_H
#define EMALLOC_H

#define HEAP_SIZE 4

#include "../Process/process.h"
#include "pmm.h"
#include "paging.h"
#include "../Terminal/terminal.h"

struct PCB;

typedef struct Heap{
    unsigned int heap_base;
    unsigned int size;
    int free;
    struct Heap* next;
}Heap;

void Emalloc_init(struct PCB* proc);
void* Emalloc(struct PCB* proc, unsigned int bytes);
void Efree(struct PCB* proc, void* ptr);
void print_heap(struct PCB* proc);




#endif