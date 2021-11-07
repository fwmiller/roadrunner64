#include <string.h>
#include <sys/ata.h>

int ata_read_parttab(atad_t atad)
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
