typedef uint32_t lba_t;

/* buf must be at least 2048 bytes and is assumed to be zeroed */
int
read_blk(lba_t lba, uint8_t *buf)
{
	int i, result;

	/* Convert lba to sector */
	uint_t sectorno = lba << 2;

	for (i = 0; i < 4; i++) {
		/* Seek to sector */
		result = ata_seek(atad_t atad, seek_t seekargs);
		if (result < 0) {
			return (-1);
		}
		/* Read sector data */
		result = ata_read(void *dev, uint8_t * b, int *len);
		if (result < 0) {
			return (-1);
		}
	}
	return 0;
}
