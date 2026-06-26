#ifndef PCI_H
#define PCI_H

#define PCI_CONFIG_ADDRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

#include "../../IO/io.h"

void pci_init();

unsigned int pci_read32(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
);

unsigned short pci_read16(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
);

unsigned char pci_read8(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
);

#endif