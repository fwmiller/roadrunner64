#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/isofs.h>

/* This routine searches a directory buffer for a path element */
static lba_t
isofs_search_dir(char *s, uint8_t * buf, int size)
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
		if (strncmp(s, file_id, rec->file_id_len) == 0) {
#if _DEBUG
			kprintf("found %s lba %u\r\n", s, rec->lba_le);
#endif
			return rec->lba_le;
		}
	}
	return 0;
}

/*
 * This routine uses a specified full path to search the file system
 * directories for a file or directory
 */
lba_t
isofs_find(char *path, uint8_t * buf, int size)
{
	int pos = 0;

	/* Look for the full path leading slash */
	if (path[pos++] != '/') {
#if _DEBUG
		kprintf("isofs_find: full path required\r\n");
#endif
		return 0;
	}
	return isofs_search_dir(path, buf, size);
}
