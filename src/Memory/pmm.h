#ifndef PMM_H
#define PMM_H

#define BITMAP_ADDR 0x50000
#define PAGE_SIZE 4096
#define MAX_PAGES 32480 //131008 Kb / 4 Kb = 32752
#define BITMAP_SIZE 1024

typedef struct {
    unsigned long long base;
    unsigned long long length;
    unsigned int type;
    unsigned int acpi;
}__attribute__((packed)) MemMapEntry;

void pmm_init();
void pmm_set(int page);
int pmm_test(int page);
void pmm_clear(int page);

void* pmm_alloc(unsigned int numpages);


#endif