#include <ctype.h>
#include <stdio.h>
#include <sys/ata.h>
#include <sys/isofs.h>

void
isofs_dump_file_id(directory_record_t rec)
{
	char *s = ((char *)rec) + sizeof(struct directory_record);

	if (s[0] == 0) {
		kprintf(".");
		return;
	}
	if (s[0] == 1) {
		kprintf("..");
		return;
	}
	for (int i = 0; i < rec->file_id_len; i++) {
		char ch = *(s + i);
		if (isprint(ch))
			kprintf("%c", ch);
		else
			kprintf("(%02x)", ch);
	}
}

void
isofs_dump_record_date(directory_record_t rec)
{
	uint8_t *rec_date = (uint8_t *) rec->record_date;
	kprintf("%02u:", rec_date[3]);
	kprintf("%02u:", rec_date[4]);
	kprintf("%02u ", rec_date[5]);
	kprintf("%02u-", rec_date[1]);
	kprintf("%02u-", rec_date[2]);
	kprintf("%04u ", rec_date[0] + 1900);
}

void
isofs_dump_flags(directory_record_t rec)
{
	uint8_t flags = rec->flags;

	if (flags & FILE_FLAGS_EXISTENCE) {
		kprintf("EXISTS");
		flags &= ~FILE_FLAGS_EXISTENCE;
		if (flags == 0)
			return;
		kprintf(" ");
	}
	if (flags & FILE_FLAGS_DIRECTORY) {
		kprintf("DIRECTORY");
		flags &= ~FILE_FLAGS_DIRECTORY;
		if (flags == 0)
			return;
		kprintf(" ");
	}
	if (flags & FILE_FLAGS_ASSOCIATED_FILE) {
		kprintf("ASSOCIATED-FILE");
		flags &= ~FILE_FLAGS_ASSOCIATED_FILE;
		if (flags == 0)
			return;
		kprintf(" ");
	}
	if (flags & FILE_FLAGS_RECORD) {
		kprintf("RECORD");
		flags &= ~FILE_FLAGS_RECORD;
		if (flags == 0)
			return;
		kprintf(" ");
	}
	if (flags & FILE_FLAGS_PROTECTION) {
		kprintf("PROTECTION");
		flags &= ~FILE_FLAGS_PROTECTION;
		if (flags == 0)
			return;
		kprintf(" ");
	}
	if (flags & FILE_FLAGS_MULTI_EXTENT)
		kprintf("MULTI-EXTENT");
}

void
isofs_dump_directory(uint8_t * buf, int size)
{
	directory_record_t rec;

	for (int pos = 0; pos < size;) {
		rec = (directory_record_t) (buf + pos);
		if (rec->dir_rec_len == 0)
			break;

		/* File id */
		isofs_dump_file_id(rec);
		kprintf("\r\n");
#if 0
		/* File creation time and date */
		isofs_dump_record_date(rec);
		kprintf("\r\n");

		kprintf("dir_rec_len %u ", rec->dir_rec_len);
		kprintf("ext_att_rec_len %u ", rec->ext_att_rec_len);
		kprintf("file_id_len %u\r\n", rec->file_id_len);

		kprintf("lba %u ", rec->lba_le);
		kprintf("size %u ", rec->size_le);

		kprintf("flags 0x%02x ", rec->flags);
		if (rec->flags > 0) {
			kprintf("(");
			isofs_dump_flags(rec);
			kprintf(")");
		}
		kprintf("\r\n");

		kprintf("unit_size %u ", rec->unit_size);
		kprintf("interleave_gap_size %u ", rec->interleave_gap_size);
		kprintf("vol_seqno %u\r\n", rec->vol_seqno_le);
#endif
		pos += rec->dir_rec_len;
	}
}
