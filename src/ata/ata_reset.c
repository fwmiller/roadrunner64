#include <ata.h>
#include <io.h>

void ata_reset(atac_t atac)
{
	/* Assert software reset */
	outb(atac->ctlbase + ATA_DEV_CONTROL, ATA_CTL_RESET);

	/*
	 * XXX Should be 5 microseconds (ATA/ATAPI-6).  This would be better
	 * implemented with the Timestamp Counter.
	 */
	ata_select_delay(atac);

	/* Clear software reset */
	outb(atac->ctlbase + ATA_DEV_CONTROL, 0);
}
