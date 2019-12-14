#include <ata.h>
#include <errno.h>

int ata_get_boot_device(uchar_t drv, char *device)
{
#if 0
	atad_t atad;
	int drive = 0, i, j;

	for (i = 0; i < ATA_DRIVES; i++) {
		atad = &(atadtab[i]);
		if (atad->type != ATA_DRV_NULL) {
			if (drive == (drv & 0x03)) {
				for (j = 0; j < PARTS; j++) {
					if (atad->parttab[j].active) {
						sprintf(device, "hd%d",
							(PARTS * drive) + j);
#if _DEBUG
						kprintf
						    ("ata_get_boot_device: ");
						kprintf
						    ("boot from partition %s\n",
						     device);
#endif
						return 0;
					}
				}
#if _DEBUG
				kprintf("ata_get_boot_device: ");
				kprintf("no active partition on ata%d\n", i);
#endif
				return ENXIO;
			}
			drive++;
		}
	}
#if _DEBUG
	kprintf("ata_get_boot_device: ");
	kprintf("illegal boot drive specified (%02x)\n", drv);
#endif
#endif
	return ENXIO;
}
