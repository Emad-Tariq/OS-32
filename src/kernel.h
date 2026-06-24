#ifndef KERNEL_H
#define KERNEL_H

#include "Terminal/terminal.h"
#include "Interrupts/idt.h"
#include "IO/io.h"
#include "Interrupts/pic.h"
#include "Interrupts/irq.h"
#include "Memory/pmm.h"
#include "Memory/Emalloc.h"
#include "Memory/paging.h"
#include "Process/process.h"
#include "Process/scheduler.h"
#include "Loader/elf.h"

extern unsigned char _binary___build_hello_elf_start[];
extern unsigned char _binary___build_hello_elf_end[];
extern unsigned int kernel_esp;

void kmain();

#endif