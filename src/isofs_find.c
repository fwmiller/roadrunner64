#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/ata.h>
#include <sys/isofs.h>
#include <sys/lex.h>

static lba_t
isofs_search_dir(char *s, uint8_t * dir, int size)
{
	directory_record_t rec;
	char *file_id;
	int len;

	len = strlen(s);
#if _DEBUG
	printf("isofs_search_dir: search for [%s] len %u\r\n", s, len);
#endif
	/* Loop over directory entries */
	for (int pos = 0; pos < size; pos += rec->dir_rec_len) {
		rec = (directory_record_t) (dir + pos);
		if (rec->dir_rec_len == 0)
			break;

		/* Check entry file id against path element */
		if (len != rec->file_id_len)
			continue;

		file_id = ((char *)rec) + sizeof(struct directory_record);
		if (strncmp(s, file_id, rec->file_id_len) == 0) {
#if _DEBUG
			printf("isofs_search_dir: found %s lba %u\r\n", s,
			       rec->lba_le);
#endif
			return rec->lba_le;
		}
	}
#if _DEBUG
	printf("isofs_search_dir: %s not found\r\n", s);
#endif
	return 0;
}

static void
nextelem(const char *ln, int *pos, char *arg)
{
	int i;
	char ch;

	/* Consume leading slashes */
	while (ln[*pos] == '/')
		(*pos)++;

	for (i = 0;; (*pos)++) {
		ch = ln[*pos];
		if (ch == '\0' || ch == '/')
			break;
		arg[i++] = ch;
	}
}

/*
 * This routine uses a specified full path to search the file system
 * directories for a file or directory
 */
lba_t
isofs_find(const char *path, uint8_t * rootdir, int size)
{
	uint8_t *dir = rootdir;
	uint8_t buf[ATAPI_SECTOR_SIZE];
	char elem[80];
	lba_t lba = 0;
	int result;

#if _DEBUG
	printf("isofs_find: path [%s]\r\n", path);
#endif
	for (int pos = 0;;) {
		/* Consume path separators */
		if (path[pos++] != '/')
			break;

		/* Get next path element to search for */
		memset(elem, 0, 80);
		nextelem(path, &pos, elem);
#if _DEBUG
		printf("isofs_find: elem [%s]\r\n", elem);
#endif
		/* Search the directory for the path element */
		if ((lba = isofs_search_dir(elem, dir, size)) == 0) {
			break;
		}
		/* Read the next directory */
		dir = buf;
		memset(buf, 0, ATAPI_SECTOR_SIZE);
		result = isofs_read_blk(ata_get_primary_partition(), lba, buf);
		if (result < 0)
			break;
	}
	return lba;
}
