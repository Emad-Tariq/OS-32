#include "fs.h"

SuperBlock supervisor;
FileEntry FileTable[MAX_FILES];

void fs_init(){
    supervisor.magic = MAGIC;
    supervisor.version = 1;

    supervisor.file_table_start = SUPER_SECTOR;
    supervisor.file_table_sectors = FILE_TABLE_SSIZE;

    supervisor.data_start = SUPER_SECTOR + FILE_TABLE_SSIZE + 1;
    supervisor.file_count = MAX_FILES;

    for(int i=0; i<MAX_FILES; i++){
        FileTable[i].name[0] = '\0';
        FileTable[i].start_lba = 0;
        FileTable[i].sectors = 0;
        FileTable[i].size = 0;
        FileTable[i].flags = FILE_VALID;
        for(int j=0; j<16; j++){
            FileTable[i].reserved[j] = 0;
        }
    }
}