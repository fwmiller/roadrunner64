#include <string.h>
#include <sys/isofs.h>

lba_t
isofs_find(char *path, uint8_t * buf, int size)
{
	directory_record_t rec;
	char *file_id;

	/* Loop over directory entries */
	for (int pos = 0; pos < size; pos += rec->dir_rec_len) {
		rec = (directory_record_t) (buf + pos);
		if (rec->dir_rec_len == 0)
			break;

		/* Check entry file id against path element */
		file_id = ((char *)rec) + sizeof(struct directory_record);
		if (strncmp(path, file_id, rec->file_id_len) == 0) {
			kprintf("found %s lba %u\r\n", path, rec->lba_le);
			return rec->lba_le;
		}
	}
	return 0;
}
