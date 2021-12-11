#include <stdio.h>
#include <sys/isofs.h>

static void
isofs_dump_path_table_record(path_table_record_t rec)
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

void
isofs_dump_path_table(primary_volume_descriptor_t pri, uint8_t * buf)
{
	kprintf("dir_id_len ext_att_rec_len lba          ");
	kprintf("parent_dirno path\r\n");

	for (int pos = 0; pos < pri->path_table_size_le;) {
		path_table_record_t rec = (path_table_record_t) (buf + pos);
		isofs_dump_path_table_record(rec);

		unsigned reclen = sizeof(struct path_table_record) +
		    rec->dir_id_len;
		if (rec->dir_id_len % 2 == 1)
			reclen++;
		pos += reclen;
	}
}
