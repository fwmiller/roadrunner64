#include <ata.h>
#include <io.h>

void ata_reset(atac_t atac)
{
	int i;

	/* Assert software reset */
	outb(atac->iobase + ATA_CONTROL, ATA_CTL_RESET);

#if 0
	/*
	 * XXX Should be 5 microseconds (ATA/ATAPI-6).  This would be better
	 * implemented with a Pentium Timestamp Counter based timer.
	 */
	DELAY(5000);
#endif
	for (i = 0; i < 5000; i++) ;

	/* Clear software reset */
	outb(atac->iobase + ATA_CONTROL, 0);
}
