#include <ata.h>
#include <io.h>

void ata_reset(atac_t atac)
{
	int i;

	/* Assert software reset */
	outb(atac->ctlbase + ATA_DEV_CONTROL, ATA_CTL_RESET);

	/*
	 * XXX Should be 5 microseconds (ATA/ATAPI-6).  This would be better
	 * implemented with a Pentium Timestamp Counter based timer.
	 */
#if 0
	DELAY(5000);
#endif
	for (i = 0; i < 5000; i++) ;

	/* Clear software reset */
	outb(atac->ctlbase + ATA_DEV_CONTROL, 0);
}
