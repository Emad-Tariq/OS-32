#ifndef EMALLOC_H
#define EMALLOC_H

#define HEAP_SIZE 2560

typedef struct Block{
    unsigned int size;
    int free;
    struct Block* next;
}Block;

void Emalloc_init();
void* Emalloc(unsigned int bytes);
void Efree(void* ptr);
void print_heap();




#endif