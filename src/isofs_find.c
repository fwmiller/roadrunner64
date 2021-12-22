#if _DEBUG
#include <stdio.h>
#endif
#include <string.h>
#include <sys/isofs.h>
#include <sys/lex.h>

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
	struct lex l;
	lba_t lba;
	int pos = 0;

#if _DEBUG
	kprintf("isofs_find: path [%s]\r\n", path);
#endif

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
			return 0;
		}
#if _DEBUG
		kprintf("isofs_find: ");
		kprintf("path element [%s]\r\n", l.s);
#endif
		/* Search the directory for the path element */
		lba = isofs_search_dir(path, buf, size);
		if (lba == 0) {
			/* Path element not found */
		}
		memset(&l, 0, sizeof(struct lex));
		nextlex(path, &pos, &l);
		if (l.type == LEX_SEMICOLON) {
			/*
			 * Found the location of the last path element 
			 * which must be a file
			 */
#if _DEBUG
			kprintf("isofs_find: found file\r\n");
#endif
			return lba;

		}
		if (l.type == LEX_EOL) {
			/*
			 * Found the location of the last path element 
			 * which must be a directory
			 */
#if _DEBUG
			kprintf("isofs_find: found directory\r\n");
#endif
			return lba;
		}
		if (l.type != LEX_SLASH)
			break;
	}
#if _DEBUG
	kprintf("isofs_find: not found\r\n");
#endif
	return 0;
}
