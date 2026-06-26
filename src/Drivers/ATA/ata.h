#ifndef ATA_H
#define ATA_H

#include "../PCI/pci.h"
#include "../../Terminal/terminal.h"

#define ATA_PRIMARY_IO      0x1F0
#define ATA_PRIMARY_CTRL    0x3F6

#define ATA_REG_DATA        0
#define ATA_REG_ERROR       1
#define ATA_REG_SECCOUNT    2
#define ATA_REG_LBA0        3
#define ATA_REG_LBA1        4
#define ATA_REG_LBA2        5
#define ATA_REG_HDDEVSEL    6
#define ATA_REG_STATUS      7
#define ATA_REG_COMMAND     7

#define ATA_SR_ERR          0x01
#define ATA_SR_IDX          0x02
#define ATA_SR_CORR         0x04
#define ATA_SR_DRQ          0x08
#define ATA_SR_DSC          0x10
#define ATA_SR_DF           0x20
#define ATA_SR_DRDY         0x40
#define ATA_SR_BSY          0x80

void ata_identify();
void ata_load();
void ata_wait();

#endif