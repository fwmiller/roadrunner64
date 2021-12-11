#include <string.h>
#include <sys/isofs.h>

lba_t
isofs_find(char *path, uint8_t * buf, int size)
{
	directory_record_t rec;
	lba_t lba;

	for (int pos = 0; pos < size;) {
		rec = (directory_record_t) (buf + pos);
		if (rec->dir_rec_len == 0)
			break;

		char *file_id = ((char *)rec) + rec->dir_rec_len;
		if (strncmp(path, file_id, rec->file_id_len) == 0) {
		}
		pos += rec->dir_rec_len;
	}
	return lba;
}
