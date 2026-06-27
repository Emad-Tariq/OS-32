#ifndef FS_STRUCTS_H
#define FS_STRUCTS_H

#define MAGIC               0x4F533332
#define SUPER_SECTOR        64
#define FILE_TABLE_SSIZE    4
#define DATA_LBA          69
#define MAX_FILES           32

#define FILE_VALID          1
#define FILE_DIRECTORY      2
#define FILE_READONLY       4

typedef struct {
    unsigned int magic;
    unsigned int version;

    unsigned int file_table_start;
    unsigned int file_table_sectors;

    unsigned int data_start;
    unsigned int file_count;
} SuperBlock;

typedef struct {
    char name[32];
    unsigned int start_lba;
    unsigned int size;
    unsigned int sectors;
    unsigned int flags;

    char reserved[16];
} FileEntry;

#endif