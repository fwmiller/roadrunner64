#include <ata.h>

int ata_read_mbr(atap_t atap, uchar_t * b, int *len)
{
	struct seek seekargs;
	int result;

	seekargs.offset = 0;
	seekargs.whence = SEEK_SET;
	result = ata_seek(atap->atad, &seekargs);
	if (result < 0)
		return result;

	result = ata_read(atap, b, len);
	if (result < 0)
		return result;

	return 0;
}
