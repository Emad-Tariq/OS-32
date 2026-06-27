#include "fs.h"

SuperBlock supervisor;
FileEntry FileTable[MAX_FILES];

void fs_init(){
    ata_read(SUPER_SECTOR, (void*)&supervisor, 1);
    if(supervisor.magic != MAGIC){
        printf("fatal: Invalid FileSystem\n");
    }

    ata_read(supervisor.file_table_start, &FileTable, supervisor.file_table_sectors);
    // printf("MAGIC: %d\n", supervisor.magic);
    // printf("VERSION: %d\n", supervisor.version);
    // printf("T START: %d\n", supervisor.file_table_start);
    // printf("T SSIZE: %d\n", supervisor.file_table_sectors);
    // printf("DATA START: %d\n", supervisor.data_start);
    // printf("F COUNT: %d\n", supervisor.file_count);

    // printf("NAME: %s\n", FileTable[0].name);
}

FileEntry* fs_find(const char* name){
    int flag = 1;
    for(int i=0; i<MAX_FILES; i++){
        flag = 1;
        for(int j=0; name[j] != '\0' && FileTable[i].name[j] != '\0'; j++){
            if(name[j] != FileTable[i].name[j]){
                flag=0;
                break;
            }
        }
        if(flag) return &FileTable[i];
    }

    printf("Could not find file: No such file\n");
    return 0;
}