#include <ata.h>
#include <io.h>

void
ata_select_delay(atac_t atac)
{
	/*
	 * ATA specifies a 400ns delay after drive switching -- often
	 * implemented as 4 Alternative Status queries
	 */
	inb(atac->ctlbase + ATA_ALT_STATUS);
	inb(atac->ctlbase + ATA_ALT_STATUS);
	inb(atac->ctlbase + ATA_ALT_STATUS);
	inb(atac->ctlbase + ATA_ALT_STATUS);
}
