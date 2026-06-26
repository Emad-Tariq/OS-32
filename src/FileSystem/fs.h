#ifndef FS_H
#define FS_H

#include "fs_structs.h"

#define MAGIC               0x4F533332
#define SUPER_SECTOR        64
#define FILE_TABLE_SSIZE    4
#define MAX_FILES           32

#define FILE_VALID          1
#define FILE_DIRECTORY      2
#define FILE_READONLY       4

void fs_init();
int fs_find(const char* name, FileEntry* file);
int fs_read(const char* name, void* buffer);

#endif