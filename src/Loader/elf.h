#ifndef ELF_H
#define ELF_H

#include "elf_structs.h"
#include "../Terminal/terminal.h"

typedef struct PCB PCB;

int load_elf(void* image, PCB* proc);

#endif