#include <ata.h>
#include <errno.h>
#include <ioctl.h>

int ata_ioctl(void *dev, int cmd, void *args)
{
#if 0
	atap_t atap = (atap_t) dev;
	atad_t atad = atap->atad;

	switch (cmd) {
	case LOCK:
		return mutex_lock(&(atad->atac->mutex));

	case UNLOCK:
		return mutex_unlock(&(atad->atac->mutex));

	case GET_GEOMETRY:
		{
			geometry_t geom;

			if (args == NULL)
				return EINVAL;
			geom = (geometry_t) args;
			geom->flags = GF_PARTITIONED;
			geom->tracks = atad->param.cylinders;
			geom->heads = atad->param.heads;
			geom->sectorspertrack = atad->param.sectors;
			geom->bytespersector = SECTOR_SIZE;
		}
		return 0;

	case GET_BIOS_GEOMETRY:
		{
			geometry_t geom;

			if (args == NULL)
				return EINVAL;
			geom = (geometry_t) args;
			geom->flags = GF_PARTITIONED;
			geom->tracks =
			    (((bootparams.sec_cyl_hi & 0xc0) << 2) |
			     bootparams.cyl_lo) + 1;
			geom->heads = bootparams.hd + 1;
			geom->sectorspertrack = bootparams.sec_cyl_hi & 0x3f;
			geom->bytespersector = SECTOR_SIZE;
		}
		return 0;

	case READ_MBR:
		{
			buf_t b;
			int result;

			if (args == NULL)
				return EINVAL;

			b = bget(SECTOR_SIZE);
			blen(b) = SECTOR_SIZE;
			result = ata_read_mbr(atap, &b);
			if (result < 0) {
				brel(b);
				return result;
			}
			bcopy(bstart(b), (char *)args, SECTOR_SIZE);
			brel(b);
		}
		return 0;

	case WRITE_MBR:
		{
			buf_t b;
			struct seek seekargs;
			int result;

			if (args == NULL)
				return EINVAL;

			/*
			 * Update partition offsets.  This relies on the knowledge
			 * that the partitions for the specified drive were allocated
			 * in order.
			 */
			{
				struct part parttab[PARTS];
				int i, partcnt = 0;

				read_parttab((uchar_t *) args, parttab);
				for (i = 0; i < PARTS * ATA_DRIVES; i++)
					if (ataptab[i].atad == atad) {
						ataptab[i].sectors =
						    parttab[partcnt].size;
						ataptab[i].offset =
						    parttab[partcnt].off;
						if (++partcnt == PARTS)
							break;
					}
			}
			seekargs.whence = SEEK_SET;
			seekargs.offset = 0;
			result = ata_seek(atad, &seekargs);
			if (result < 0)
				return result;

			b = bget(SECTOR_SIZE);
			blen(b) = SECTOR_SIZE;
			bcopy((char *)args, bstart(b), SECTOR_SIZE);
			result = ata_write(atap, &b);
			if (result < 0) {
				if (b != NULL)
					brel(b);
				return result;
			}
		}
		return 0;

	case GET_PART_OFF:
		if (args == NULL)
			return EINVAL;
		*((ulong_t *) args) = atap->offset;
		return 0;

	case GET_PART_SIZE:
		if (args == NULL)
			return EINVAL;
		*((ulong_t *) args) = atap->sectors;
		return 0;

	case GET_BUFFER_SIZE:
		if (args == NULL)
			return EINVAL;
		*((ulong_t *) args) = SECTOR_SIZE;
		return 0;

	case SEEK_BLOCK:
		if (args == NULL)
			return EINVAL;
		((seek_t) args)->offset += atap->offset;
		return ata_seek(atad, (seek_t) args);

		//default:
	}
#endif
	return ENOTTY;
}
