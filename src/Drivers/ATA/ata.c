#include "ata.h"


void ata_identify(){
    outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
    ata_load();

    outb(ATA_PRIMARY_IO + ATA_REG_SECCOUNT, 0);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA0, 0);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA1, 0);
    outb(ATA_PRIMARY_IO + ATA_REG_LBA2, 0);
    outb(ATA_PRIMARY_IO + ATA_REG_COMMAND, 0xEC);

    ata_wait();

    unsigned short data[256];
    for(int i=0; i<256; i++){
        data[i] = inw(ATA_PRIMARY_IO + ATA_REG_DATA);
    }

    printf("ATA: %x %x %x %x %x\n", data[0], data[49], data[53], data[60], data[61]);
    char model[41];

    for(int i = 27; i <= 46; i++)
    {
        model[(i - 27) * 2]     = data[i] >> 8;
        model[(i - 27) * 2 + 1] = data[i] & 0xFF;
    }

    model[40] = '\0';
    printf("Model: %s\n", model);
    char serial[21];

    for(int i = 10; i <= 19; i++)
    {
        serial[(i - 10) * 2]     = data[i] >> 8;
        serial[(i - 10) * 2 + 1] = data[i] & 0xFF;
    }

    serial[20] = '\0';

    printf("Serial: %s\n", serial);
    char firmware[9];

    for(int i = 23; i <= 26; i++)
    {
        firmware[(i - 23) * 2]     = data[i] >> 8;
        firmware[(i - 23) * 2 + 1] = data[i] & 0xFF;
    }

    firmware[8] = '\0';

    printf("Firmware: %s\n", firmware);
    unsigned int sectors =
    ((unsigned int)data[61] << 16) | data[60];

    printf("Sectors: %d\n", sectors);
}

void ata_load(){
    inb(ATA_PRIMARY_CTRL);
    inb(ATA_PRIMARY_CTRL);
    inb(ATA_PRIMARY_CTRL);
    inb(ATA_PRIMARY_CTRL);
}
void ata_wait(){
    while (1) {
        unsigned char status = inb(ATA_PRIMARY_IO + ATA_REG_STATUS);

        if (status & ATA_SR_ERR) {
            printf("ATA Error\n");
            return;
        }

        if (!(status & ATA_SR_BSY) && (status & ATA_SR_DRQ))
            break;
    }
}