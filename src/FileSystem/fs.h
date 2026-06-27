#ifndef FS_H
#define FS_H

#include "fs_structs.h"
#include "../Terminal/terminal.h"
#include "../Drivers/ATA/ata.h"

void fs_init();
FileEntry* fs_find(const char* name);
int fs_read(const char* name, void* buffer);

#endif