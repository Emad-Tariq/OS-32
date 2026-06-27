#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "../FileSystem/fs_structs.h"



int is_elf(const char *name)
{
    const char *ext = strrchr(name, '.');
    return ext && strcmp(ext, ".elf") == 0;
}

int main(){
    printf("Creating File System\n");
    FILE* disk = fopen("bin/disk.img", "rb+");
    if(!disk){
        perror("fopen");
        return 1;
    }
    SuperBlock sb = {
        .magic = MAGIC,
        .version = 1,
        .file_table_start = SUPER_SECTOR + 1,
        .file_table_sectors = FILE_TABLE_SSIZE,
        .data_start = DATA_LBA,
        .file_count = 0
    };

    DIR* dir = opendir("build/user");
    if(!dir){
        perror("opendir");
        return 1;
    }
    struct dirent* entry;
    unsigned int sector = sb.data_start;
    unsigned int cur = sb.file_table_start * 512;

    while((entry = readdir(dir)) != NULL){
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

        if (!is_elf(entry->d_name)) continue;

        char path[32];
        snprintf(path, sizeof(path), "build/user/%s", entry->d_name);

        FILE* elf = fopen(path, "rb");
        if(!elf) continue;

        fseek(elf, 0, SEEK_END);
        long size = ftell(elf);
        rewind(elf);

        FileEntry file = {0};
        file.flags = FILE_VALID;
        file.size = size;
        file.sectors = (size + 511) / 512;
        file.start_lba = sector;
        strncpy(file.name, entry->d_name, sizeof(file.name) - 1);

        char buffer[512];
        fseek(disk, cur, SEEK_SET);
        fwrite(&file, sizeof(FileEntry), 1, disk);
        fseek(disk, 512*sector, SEEK_SET);

        while (1) {
            size_t n = fread(buffer, 1, sizeof(buffer), elf);

            if (n == 0)
                break;

            fwrite(buffer, 1, n, disk);
        }

        fclose(elf);
        printf("File: %s loaded at LBA: %d\n", entry->d_name, file.start_lba);
        cur += sizeof(FileEntry);
        sector += file.sectors;
        sb.file_count++;
    }

    fseek(disk, 64 * 512, SEEK_SET);
    fwrite(&sb, sizeof(SuperBlock), 1, disk);

    closedir(dir);
    fclose(disk);
}