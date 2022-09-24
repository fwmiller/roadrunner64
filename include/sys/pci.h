#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>

#define PCI_BUSSES 4
#define PCI_SLOTS 32
#define PCI_TAB_SIZE (PCI_BUSSES * PCI_SLOTS)

/* Ports for access to PCI config space */
#define PCI_CONFIG_ADDR 0xcf8
#define PCI_CONFIG_DATA 0xcfc

/* PCI config space register offsets */
#define PCI_CONFIG_VENDOR 0
#define PCI_CONFIG_CMD_STAT 1
#define PCI_CONFIG_CLASS_REV 2
#define PCI_CONFIG_HDR_TYPE 3
#define PCI_CONFIG_BASE_ADDR_0 4
#define PCI_CONFIG_BASE_ADDR_1 5
#define PCI_CONFIG_BASE_ADDR_2 6
#define PCI_CONFIG_BASE_ADDR_3 7
#define PCI_CONFIG_BASE_ADDR_4 8
#define PCI_CONFIG_BASE_ADDR_5 9
#define PCI_CONFIG_CIS 10
#define PCI_CONFIG_SUBSYSTEM 11
#define PCI_CONFIG_ROM 12
#define PCI_CONFIG_CAPABILITIES 13
#define PCI_CONFIG_INTR 15

/* PCI vendor IDs */
#define PCI_VENDOR_COMPAQ 0x0e11
#define PCI_VENDOR_NCR 0x1000
#define PCI_VENDOR_ATI 0x1002
#define PCI_VENDOR_VLSI 0x1004
#define PCI_VENDOR_TSENG 0x100c
#define PCI_VENDOR_WEITEK 0x100e
#define PCI_VENDOR_DEC 0x1011
#define PCI_VENDOR_CIRRUS 0x1013
#define PCI_VENDOR_IBM 0x1014
#define PCI_VENDOR_AMD 0x1022
#define PCI_VENDOR_TRIDENT 0x1023
#define PCI_VENDOR_MATROX 0x102b
#define PCI_VENDOR_NEC 0x1033
#define PCI_VENDOR_HP 0x103c
#define PCI_VENDOR_BUSLOGIC 0x104b
#define PCI_VENDOR_TI 0x104c
#define PCI_VENDOR_MOTOROLA 0x1057
#define PCI_VENDOR_NUMBER9 0x105d
#define PCI_VENDOR_APPLE 0x106b
#define PCI_VENDOR_CYRIX 0x1078
#define PCI_VENDOR_SUN 0x108e
#define PCI_VENDOR_3COM 0x10b7
#define PCI_VENDOR_ACER 0x10b9
#define PCI_VENDOR_MITSUBISHI 0x10ba
#define PCI_VENDOR_NVIDIA 0x10de
#define PCI_VENDOR_FORE 0x1127
#define PCI_VENDOR_PHILLIPS 0x1131
#define PCI_VENDOR_RENDITION 0x1163
#define PCI_VENDOR_TOSHIBA 0x1179
#define PCI_VENDOR_QEMU 0x1234
#define PCI_VENDOR_ENSONIQ 0x1274
#define PCI_VENDOR_ROCKWELL 0x127a
#define PCI_VENDOR_NETGEAR 0x1385
#define PCI_VENDOR_VMWARE 0x15ad
#define PCI_VENDOR_VIRTIO 0x1af4
#define PCI_VENDOR_S3 0x5333
#define PCI_VENDOR_INTEL 0x8086
#define PCI_VENDOR_ADAPTEC 0x9004
#define PCI_VENDOR_ADAPTEC2 0x9005

/* PCI function classes */
#define PCI_CLASS_PRE 0
#define PCI_CLASS_STORAGE 0x01
#define PCI_CLASS_NETWORK 0x02
#define PCI_CLASS_DISPLAY 0x03
#define PCI_CLASS_MULTIMEDIA 0x04
#define PCI_CLASS_MEMORY 0x05
#define PCI_CLASS_BRIDGE 0x06
#define PCI_CLASS_COMM 0x07
#define PCI_CLASS_BASE 0x08
#define PCI_CLASS_INPUT 0x09
#define PCI_CLASS_DOCK 0x0a
#define PCI_CLASS_CPU 0x0b
#define PCI_CLASS_SERIAL 0x0c
#define PCI_CLASS_WIRELESS 0x0d
#define PCI_CLASS_IIO 0x0e
#define PCI_CLASS_SATELLITE 0x0f
#define PCI_CLASS_SEC 0x10
#define PCI_CLASS_DSP 0x11

/* PCI storage function subclasses */
#define PCI_STORAGE_SCSI 0
#define PCI_STORAGE_IDE 1
#define PCI_STORAGE_FLOPPY 2
#define PCI_STORAGE_RAID 4

/* PCI network function subclasses */
#define PCI_NETWORK_ETHERNET 0
#define PCI_NETWORK_TOKEN 1
#define PCI_NETWORK_FDDI 2
#define PCI_NETWORK_ATM 3
#define PCI_NETWORK_ISDN 4

/* PCI display function subclasses */
#define PCI_DISPLAY_VGA 0
#define PCI_DISPLAY_XGA 1
#define PCI_DISPLAY_3D 2

/* PCI multimedia function subclasses */
#define PCI_MULTIMEDIA_VIDEO 0
#define PCI_MULTIMEDIA_AUDIO 1
#define PCI_MULTIMEDIA_TELEPHONY 2

/* PCI memory controller function subclasses */
#define PCI_MEMORY_RAM 0
#define PCI_MEMORY_FLASH 1

/* PCI bridge function subclasses */
#define PCI_BRIDGE_HOST 0
#define PCI_BRIDGE_ISA 1
#define PCI_BRIDGE_EISA 2
#define PCI_BRIDGE_MICROCHAN 3
#define PCI_BRIDGE_PCI 4
#define PCI_BRIDGE_PCMCIA 5
#define PCI_BRIDGE_NUBUS 6
#define PCI_BRIDGE_CARDBUS 7
#define PCI_BRIDGE_RACEWAY 8

/* PCI serial bus controller function subclasses */
#define PCI_SERIAL_IEEE1394 0
#define PCI_SERIAL_USB 3
#define PCI_SERIAL_FIBRE_CHANNEL 4

struct pci_func {
    int bus, dev, func; /* Function logical address */
    uint16_t vendorid;  /* Vendor id */
    uint16_t deviceid;  /* Device id */
    uint8_t class;      /* Device class */
    uint8_t subclass;   /* Device subclass */
    uint32_t iobase;    /* I/O registers base addr */
    int irq;            /* Interrupt number */
};

typedef struct pci_func *pci_func_t;

extern struct pci_func pcitab[];
extern int pcifuncs;

uint32_t pci_config_read(int bus, int dev, int func, int dword);
void pci_init();
pci_func_t pci_lookup(uint8_t class, uint8_t subclass);

#endif
