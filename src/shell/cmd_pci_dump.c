#include <stdio.h>
#include <sys/pci.h>

void
dump_pci_vendorid(uint32_t vendorid) {
    switch (vendorid) {
    case PCI_VENDOR_COMPAQ:
        printf("Compaq    ");
        break;
    case PCI_VENDOR_NCR:
        printf("NCR       ");
        break;
    case PCI_VENDOR_ATI:
        printf("ATI       ");
        break;
    case PCI_VENDOR_VLSI:
        printf("VLSI      ");
        break;
    case PCI_VENDOR_TSENG:
        printf("Tseng     ");
        break;
    case PCI_VENDOR_WEITEK:
        printf("Weitek    ");
        break;
    case PCI_VENDOR_DEC:
        printf("DEC       ");
        break;
    case PCI_VENDOR_CIRRUS:
        printf("Cirrus    ");
        break;
    case PCI_VENDOR_IBM:
        printf("IBM       ");
        break;
    case PCI_VENDOR_AMD:
        printf("AMD       ");
        break;
    case PCI_VENDOR_TRIDENT:
        printf("Trident   ");
        break;
    case PCI_VENDOR_MATROX:
        printf("Matrox    ");
        break;
    case PCI_VENDOR_NEC:
        printf("NEC       ");
        break;
    case PCI_VENDOR_HP:
        printf("HP        ");
        break;
    case PCI_VENDOR_BUSLOGIC:
        printf("Buslogic  ");
        break;
    case PCI_VENDOR_TI:
        printf("TI        ");
        break;
    case PCI_VENDOR_MOTOROLA:
        printf("Motorola  ");
        break;
    case PCI_VENDOR_NUMBER9:
        printf("Number9   ");
        break;
    case PCI_VENDOR_APPLE:
        printf("Apple     ");
        break;
    case PCI_VENDOR_CYRIX:
        printf("Cyrix     ");
        break;
    case PCI_VENDOR_SUN:
        printf("Sun       ");
        break;
    case PCI_VENDOR_3COM:
        printf("3Com      ");
        break;
    case PCI_VENDOR_ACER:
        printf("Acer      ");
        break;
    case PCI_VENDOR_MITSUBISHI:
        printf("Mitsubishi");
        break;
    case PCI_VENDOR_NVIDIA:
        printf("Nvidia    ");
        break;
    case PCI_VENDOR_FORE:
        printf("Fore      ");
        break;
    case PCI_VENDOR_PHILLIPS:
        printf("Phillips  ");
        break;
    case PCI_VENDOR_RENDITION:
        printf("Rendition ");
        break;
    case PCI_VENDOR_TOSHIBA:
        printf("Toshiba   ");
        break;
    case PCI_VENDOR_QEMU:
        printf("QEMU      ");
        break;
    case PCI_VENDOR_ENSONIQ:
        printf("Ensoniq   ");
        break;
    case PCI_VENDOR_ROCKWELL:
        printf("Rockwell  ");
        break;
    case PCI_VENDOR_NETGEAR:
        printf("Netgear   ");
        break;
    case PCI_VENDOR_VMWARE:
        printf("VMWare    ");
        break;
    case PCI_VENDOR_VIRTIO:
        printf("Virtio    ");
        break;
    case PCI_VENDOR_S3:
        printf("S3        ");
        break;
    case PCI_VENDOR_INTEL:
        printf("Intel     ");
        break;
    case PCI_VENDOR_ADAPTEC:
        printf("Adaptec   ");
        break;
    case PCI_VENDOR_ADAPTEC2:
        printf("Adaptec2  ");
        break;
    default:
        printf("Unknown   ");
    }
}

void
dump_pci_class(uint8_t class) {
    switch (class) {
    /* PCI function classes */
    case PCI_CLASS_PRE:
        printf("Pre       ");
        break;
    case PCI_CLASS_STORAGE:
        printf("Storage   ");
        break;
    case PCI_CLASS_NETWORK:
        printf("Network   ");
        break;
    case PCI_CLASS_DISPLAY:
        printf("Display   ");
        break;
    case PCI_CLASS_MULTIMEDIA:
        printf("Multimedia");
        break;
    case PCI_CLASS_MEMORY:
        printf("Memory    ");
        break;
    case PCI_CLASS_BRIDGE:
        printf("Bridge    ");
        break;
    case PCI_CLASS_COMM:
        printf("Comm      ");
        break;
    case PCI_CLASS_BASE:
        printf("Base      ");
        break;
    case PCI_CLASS_INPUT:
        printf("Input     ");
        break;
    case PCI_CLASS_DOCK:
        printf("Dock      ");
        break;
    case PCI_CLASS_CPU:
        printf("CPU       ");
        break;
    case PCI_CLASS_SERIAL:
        printf("Serial    ");
        break;
    case PCI_CLASS_WIRELESS:
        printf("Wireless  ");
        break;
    case PCI_CLASS_IIO:
        printf("IIO       ");
        break;
    case PCI_CLASS_SATELLITE:
        printf("Satellite ");
        break;
    case PCI_CLASS_SEC:
        printf("SEC       ");
        break;
    case PCI_CLASS_DSP:
        printf("DSP       ");
        break;
    default:
        printf("Unknown   ");
    }
}

void
dump_pci_subclass(uint8_t class, uint8_t subclass) {
}
