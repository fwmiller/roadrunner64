#include <stdio.h>
#include <sys/pci.h>

void
dump_pci_vendorid(uint32_t vendorid) {
    switch (vendorid) {
    case PCI_VENDOR_IBM:
        printf("IBM       ");
        break;
    case PCI_VENDOR_AMD:
        printf("AMD       ");
        break;
    case PCI_VENDOR_MOTOROLA:
        printf("Motorola  ");
        break;
    case PCI_VENDOR_NVIDIA:
        printf("Nvidia    ");
        break;
    case PCI_VENDOR_REALTEK:
        printf("Realtek   ");
        break;
    case PCI_VENDOR_QEMU:
        printf("QEMU      ");
        break;
    case PCI_VENDOR_VMWARE:
        printf("VMWare    ");
        break;
    case PCI_VENDOR_VIRTIO:
        printf("Virtio    ");
        break;
    case PCI_VENDOR_INTEL:
        printf("Intel     ");
        break;
    default:
        printf("          ");
    }
}

void
dump_pci_class(uint8_t devclass) {
    switch (devclass) {
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
        printf("          ");
    }
}
