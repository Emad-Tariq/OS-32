#include "pci.h"
#include "../../Terminal/terminal.h"

void pci_init(){
    unsigned int data = pci_read32(0, 0, 0, 0);

    printf("PCI: %x\n", data);
    unsigned short vendor =
    pci_read16(0, 0, 0, 0x00);

    unsigned short device =
        pci_read16(0, 0, 0, 0x02);

    printf(
        "Vendor: %x Device: %x\n",
        vendor,
        device
    );
    for(int bus = 0; bus < 256; bus++)
    {
        for(int dev = 0; dev < 32; dev++)
        {
            for(int funct = 0; funct < 8; funct++){
                unsigned short vendor =
                    pci_read16(bus, dev, funct, 0x00);

                if(vendor == 0xFFFF)
                    continue;

                unsigned short device =
                    pci_read16(bus, dev, funct, 0x02);

                unsigned char class =
                    pci_read8(bus, dev, funct, 0x0B);

                unsigned char subclass =
                    pci_read8(bus, dev, funct, 0x0A);

                unsigned char progif =
                    pci_read8(bus, dev, funct, 0x09);

                printf(
                    "Bus:%d Dev:%d Vendor:%x Device:%x Class:%x Sub:%x IF:%x\n",
                    bus,
                    dev,
                    vendor,
                    device,
                    class,
                    subclass,
                    progif
                );
            }
        }
    }
    unsigned int bar0 = pci_read32(0, 1, 1, 0x10);
    unsigned int bar1 = pci_read32(0, 1, 1, 0x14);
    unsigned int bar2 = pci_read32(0, 1, 1, 0x18);
    unsigned int bar3 = pci_read32(0, 1, 1, 0x1C);
    unsigned int bar4 = pci_read32(0, 1, 1, 0x20);
    unsigned int bar5 = pci_read32(0, 1, 1, 0x24);
    printf("Bar0: %x\n", bar0);
    printf("Bar1: %x\n", bar1);
    printf("Bar2: %x\n", bar2);
    printf("Bar3: %x\n", bar3);
    printf("Bar4: %x\n", bar4);
    printf("Bar5: %x\n", bar5);
}

unsigned int pci_read32(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
){
    unsigned int address = (
        0x80000000 | 
        (bus << 16)|
        (device << 11)|
        (function << 8)|
        (offset & 0xFC)
    );

    outl(PCI_CONFIG_ADDRESS, address);
    return inl(PCI_CONFIG_DATA);
}
unsigned short pci_read16(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
){
    unsigned int data = pci_read32(bus, device, function, offset);
    return (data >> ((offset & 2) * 8)) & 0xFFFF;
}
unsigned char pci_read8(
    unsigned char bus,
    unsigned char device,
    unsigned char function,
    unsigned char offset
){
    unsigned int data = pci_read32(bus, device, function, offset);
    return (data >> ((offset & 3) * 8)) & 0xFF;
}