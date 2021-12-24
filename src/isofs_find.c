#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/ata.h>
#include <sys/isofs.h>
#include <sys/lex.h>

/* This routine searches a directory buffer for a path element */
static lba_t
isofs_search_dir(char *s, uint8_t * dir, int size)
{
	directory_record_t rec;
	char *file_id;

	/* Loop over directory entries */
	for (int pos = 0; pos < size; pos += rec->dir_rec_len) {
		rec = (directory_record_t) (dir + pos);
		if (rec->dir_rec_len == 0)
			break;

		/* Check entry file id against path element */
		file_id = ((char *)rec) + sizeof(struct directory_record);
		if (strncmp(s, file_id, rec->file_id_len) == 0) {
#if _DEBUG
			kprintf("isofs_search_dir: found %s lba %u\r\n", s,
				rec->lba_le);
#endif
			return rec->lba_le;
		}
	}
#if _DEBUG
	kprintf("isofs_search_dir: %s not found\r\n", s);
#endif
	return 0;
}

static lba_t
isofs_found_file(lba_t lba)
{
#if _DEBUG
	kprintf("isofs_found_file: found file\r\n");
#endif
	/* XXX Skip over the version number appended to the file name */

	return lba;
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
	struct lex l;
	lba_t lba;
	int pos = 0, result;

	/* Look for the full path leading slash */
	if (path[pos++] != '/') {
#if _DEBUG
		kprintf("isofs_find: full path required\r\n");
#endif
		return 0;
	}
	for (;;) {
		/* Get the next path element */
		memset(&l, 0, sizeof(struct lex));
		nextlex(path, &pos, &l);
		if (l.type != LEX_ID) {
#if _DEBUG
			kprintf("isofs_find: ");
			kprintf("illegal path element\r\n");
#endif
			break;
		}
		/* Search the directory for the path element */
		if ((lba = isofs_search_dir(l.s, dir, size)) == 0)
			break;

		/* Path element found */
		memset(&l, 0, sizeof(struct lex));
		nextlex(path, &pos, &l);
		if (l.type == LEX_EOL)
			return lba;

		if (l.type == LEX_SEMICOLON)
			return isofs_found_file(lba);

		if (l.type != LEX_SLASH)
			break;

		/* Read the next directory */
		dir = buf;
		memset(buf, 0, ATAPI_SECTOR_SIZE);
		result = isofs_read_blk(ata_get_primary_partition(), lba, buf);
		if (result < 0)
			break;
	}
#if _DEBUG
	kprintf("isofs_find: not found\r\n");
#endif
	return 0;
}
