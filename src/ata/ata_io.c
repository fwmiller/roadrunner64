#include <errno.h>
#include <sys/ata.h>
#include <sys/i8259.h>
#include <sys/io.h>

static const int ATA_WAIT_ITERATIONS = 10000;

uint8_t
ata_inb(atac_t atac, uint16_t port) {
    return inb(atac->iobase + port);
}

void
ata_outb(atac_t atac, uint16_t port, uint8_t val) {
    outb(atac->iobase + port, val);
}

void
ata_select_delay(atac_t atac) {
    /*
     * ATA specifies a 400ns delay after drive switching -- often
     * implemented as 4 Alternative Status queries
     */
    inb(atac->ctlbase + ATA_ALT_STATUS);
    inb(atac->ctlbase + ATA_ALT_STATUS);
    inb(atac->ctlbase + ATA_ALT_STATUS);
    inb(atac->ctlbase + ATA_ALT_STATUS);
}

int
ata_wait(atac_t atac, uint8_t cmd, uint8_t mask) {
    int i;
    uint8_t status;

    for (i = 0; i < ATA_WAIT_ITERATIONS; i++) {
        status = inb(atac->ctlbase + ATA_ALT_STATUS);
        if (!(status & ATA_STAT_BSY)) {
            if (status & ATA_STAT_ERR) {
                switch (cmd) {
                case ATA_CMD_READ:
                    return EDEVREAD;
                case ATA_CMD_WRITE:
                    return EDEVWRITE;
                }
                return ENOSYS;
            }
            if ((status & (mask)) == (mask))
                break;
        }
    }
    return 0;
}

void
ata_eoi(atac_t atac) {
    /* Clear drive interrupt */
    inb(atac->iobase + ATA_STATUS);

    /* Clear interrupt controllers */
    if (atac->iobase == ATA0_IOBASE)
        outb(I8259_SLV_CTRL, I8259_EOI_HD);
    else
        outb(I8259_SLV_CTRL, I8259_EOI_HD + 1);
    outb(I8259_MSTR_CTRL, I8259_EOI_CAS);
}

void
ata_reset(atac_t atac) {
    /* Assert software reset */
    outb(atac->ctlbase + ATA_DEV_CONTROL, ATA_CTL_RESET);

    /*
     * TODO: Should be 5 microseconds (ATA/ATAPI-6).  This would be better
     * implemented with the Timestamp Counter.
     */
    ata_select_delay(atac);

    /* Clear software reset */
    outb(atac->ctlbase + ATA_DEV_CONTROL, 0);
}
