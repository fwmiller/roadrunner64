#include <ata.h>
#include <i8259.h>
#include <io.h>

void ata_eoi(atac_t atac)
{
	/* Clear drive interrupt */
	inb(atac->iobase + ATA_STATUS);

	/* Clear interrupt controllers */
	if (atac->iobase == ATA0_IOBASE)
		outb(I8259_SLV_CTRL, I8259_EOI_HD);
	else
		outb(I8259_SLV_CTRL, I8259_EOI_HD + 1);
	outb(I8259_MSTR_CTRL, I8259_EOI_CAS);
}
