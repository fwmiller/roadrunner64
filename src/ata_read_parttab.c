#include <string.h>
#include <sys/ata.h>

static int
ata_read_mbr(atap_t atap, uint8_t * b, int *len)
{
	struct seek seekargs;
	int result;

	seekargs.offset = 0;
	seekargs.whence = SEEK_SET;
	result = ata_seek(atap->atad, &seekargs);
	if (result < 0)
		return result;

	result = ata_read(atap, b, *len);
	if (result < 0)
		return result;

	return 0;
}

int
ata_read_parttab(atad_t atad)
{
	uint8_t b[SECTOR_SIZE];
	struct ata_partition atap;
	int len, result;

	memset(b, 0, SECTOR_SIZE);
	atap.atad = atad;
	atap.sectors = 0;
	atap.offset = 0;
	len = SECTOR_SIZE;
	result = ata_read_mbr(&atap, b, &len);
	if (result < 0)
		return result;

	load_parttab(b, atad->parttab);
	return 0;
}
