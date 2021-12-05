#include <ctype.h>
#include <stdio.h>
#include <sys/ata.h>
#include <sys/iso9660.h>

void iso9660_dump_primary_volume(primary_volume_descriptor_t pri)
{
	int i;

	kprintf("ISO9660 primary volume\r\n");

	kprintf("system identifier [");
	for (i = 0; i < 32; i++)
		kprintf("%c", pri->sys_id[i]);
	kprintf("]\r\n");

	kprintf("volume identifier [");
	for (i = 0; i < 32; i++)
		kprintf("%c", pri->vol_id[i]);
	kprintf("]\r\n");

	kprintf("%u blks (%u MB)\r\n",
		pri->vol_space_size_le,
		pri->vol_space_size_le * ATAPI_SECTOR_SIZE / 0x100000);

	kprintf("logical blk size %u bytes\r\n", pri->logical_blk_size_le);
	kprintf("path table size %u bytes\r\n", pri->path_table_size_le);
	kprintf("path table location blk %u\r\n", pri->path_table_loc_le);
}

static void iso9660_dump_path_table_record(path_table_record_t rec)
{
	kprintf("%10u ", rec->dir_id_len);
	kprintf("%15u ", rec->ext_att_rec_len);
	kprintf("%12u ", rec->lba);
	kprintf("%12u ", rec->parent_dirno);

	for (int i = 0; i < rec->dir_id_len; i++) {
		char *str = ((char *)rec) + sizeof(struct path_table_record);
		kprintf("%c", *(str + i));
	}
	kprintf("\r\n");
}

void iso9660_dump_path_table(primary_volume_descriptor_t pri, uint8_t * buf)
{
	kprintf("dir_id_len ext_att_rec_len lba          ");
	kprintf("parent_dirno path\r\n");

	for (int pos = 0; pos < pri->path_table_size_le;) {
		path_table_record_t rec = (path_table_record_t) (buf + pos);
		iso9660_dump_path_table_record(rec);

		unsigned reclen = sizeof(struct path_table_record) +
		    rec->dir_id_len;
		if (rec->dir_id_len % 2 == 1)
			reclen++;
		pos += reclen;
	}
}

void
iso9660_dump_file_id(directory_record_t rec)
{
	char *s = ((char *) rec) + sizeof(struct directory_record);

	for (int i = 0; i < rec->file_id_len; i++) {
		char ch = *(s + i);
		if (isprint(ch))
			kprintf("%c", ch);
		else
			kprintf("(%02x)", ch);
	}
}

void
iso9660_dump_record_date(directory_record_t rec)
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
iso9660_dump_flags(directory_record_t rec)
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

void iso9660_dump_directory(uint8_t * buf, int size)
{
	directory_record_t rec;

	for (int pos = 0; pos < size;) {
		rec = (directory_record_t) (buf + pos);
		if (rec->dir_rec_len == 0)
			break;

		kprintf("\r\n[");
		iso9660_dump_file_id(rec);
		kprintf("]\r\n");

		kprintf("created ");
		iso9660_dump_record_date(rec);
		kprintf("\r\n");

		kprintf("dir_rec_len %u ", rec->dir_rec_len);
		kprintf("ext_att_rec_len %u ", rec->ext_att_rec_len);
		kprintf("file_id_len %u\r\n", rec->file_id_len);
		kprintf("lba %u ", rec->lba_le);
		kprintf("size %u ", rec->size_le);

		kprintf("flags 0x%02x ", rec->flags);
		if (rec->flags > 0) {
			kprintf("(");
			iso9660_dump_flags(rec);
			kprintf(")");
		}
		kprintf("\r\n");

		kprintf("unit_size %u ", rec->unit_size);
		kprintf("interleave_gap_size %u ", rec->interleave_gap_size);
		kprintf("vol_seqno %u\r\n", rec->vol_seqno_le);

		pos += rec->dir_rec_len;
	}
}
