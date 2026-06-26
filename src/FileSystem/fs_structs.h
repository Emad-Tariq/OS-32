#ifndef FS_STRUCTS_H
#define FS_STRUCTS_H

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