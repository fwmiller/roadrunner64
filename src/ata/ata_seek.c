#include <errno.h>
#include <sys/ata.h>

int
ata_seek(atad_t atad, uint32_t blkno) {
    atad->blkno = blkno;
    atad->track = atad->blkno / (atad->heads * atad->sectorspertrack);
    atad->head = (atad->blkno / atad->sectorspertrack) % atad->heads;
    atad->sector = atad->blkno % atad->sectorspertrack + 1;
    return 0;
}
