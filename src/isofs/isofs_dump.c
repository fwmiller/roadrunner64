#include <ctype.h>
#include <stdio.h>
#include <sys/isofs.h>

void bufdump(char *buf, int size);

void
isofs_dump_file_id(directory_record_t rec) {
    char *s = ((char *) rec) + sizeof(struct directory_record);

    if (s[0] == 0) {
        printf(".");
        return;
    }
    if (s[0] == 1) {
        printf("..");
        return;
    }
    for (int i = 0; i < rec->file_id_len; i++) {
        char ch = *(s + i);
        if (isprint(ch))
            printf("%c", ch);
        else
            printf("(%02x)", ch);
    }
}

void
isofs_dump_record_date(directory_record_t rec) {
    uint8_t *rec_date = (uint8_t *) rec->record_date;
    printf("%02u:", rec_date[3]);
    printf("%02u:", rec_date[4]);
    printf("%02u ", rec_date[5]);
    printf("%02u-", rec_date[1]);
    printf("%02u-", rec_date[2]);
    printf("%04u ", rec_date[0] + 1900);
}

void
isofs_dump_flags(directory_record_t rec) {
    uint8_t flags = rec->flags;

    if (flags & FILE_FLAGS_EXISTENCE) {
        printf("EXISTS");
        flags &= ~FILE_FLAGS_EXISTENCE;
        if (flags == 0)
            return;
        printf(" ");
    }
    if (flags & FILE_FLAGS_DIRECTORY) {
        printf("DIRECTORY");
        flags &= ~FILE_FLAGS_DIRECTORY;
        if (flags == 0)
            return;
        printf(" ");
    }
    if (flags & FILE_FLAGS_ASSOCIATED_FILE) {
        printf("ASSOCIATED-FILE");
        flags &= ~FILE_FLAGS_ASSOCIATED_FILE;
        if (flags == 0)
            return;
        printf(" ");
    }
    if (flags & FILE_FLAGS_RECORD) {
        printf("RECORD");
        flags &= ~FILE_FLAGS_RECORD;
        if (flags == 0)
            return;
        printf(" ");
    }
    if (flags & FILE_FLAGS_PROTECTION) {
        printf("PROTECTION");
        flags &= ~FILE_FLAGS_PROTECTION;
        if (flags == 0)
            return;
        printf(" ");
    }
    if (flags & FILE_FLAGS_MULTI_EXTENT)
        printf("MULTI-EXTENT");
}

void
isofs_dump_primary_volume(primary_volume_descriptor_t pri) {
#if 0
    int i;
#endif
    printf("ISO9660 primary volume\r\n");
#if 0
    printf("system identifier [");
    for (i = 0; i < 32; i++)
        printf("%c", pri->sys_id[i]);
    printf("]\r\n");

    printf("volume identifier [");
    for (i = 0; i < 32; i++)
        printf("%c", pri->vol_id[i]);
    printf("]\r\n");
#endif
    printf("%u blks (%u MB)\r\n", pri->vol_space_size_le,
           pri->vol_space_size_le * ATAPI_SECTOR_SIZE / 0x100000);

    printf("logical blk size %u bytes\r\n", pri->logical_blk_size_le);
    printf("path table size %u bytes\r\n", pri->path_table_size_le);
    printf("path table location blk %u\r\n", pri->path_table_loc_le);
}

static void
isofs_dump_path_table_record(path_table_record_t rec) {
    printf("%10u ", rec->dir_id_len);
    printf("%15u ", rec->ext_att_rec_len);
    printf("%12u ", rec->lba);
    printf("%12u ", rec->parent_dirno);

    for (int i = 0; i < rec->dir_id_len; i++) {
        char *str = ((char *) rec) + sizeof(struct path_table_record);
        printf("%c", *(str + i));
    }
    printf("\r\n");
}

void
isofs_dump_path_table(primary_volume_descriptor_t pri, uint8_t *buf) {
    printf("dir_id_len ext_att_rec_len          lba ");
    printf("parent_dirno path\r\n");

    for (int pos = 0; pos < pri->path_table_size_le;) {
        path_table_record_t rec = (path_table_record_t)(buf + pos);
        isofs_dump_path_table_record(rec);

        unsigned reclen = sizeof(struct path_table_record) + rec->dir_id_len;
        if (rec->dir_id_len % 2 == 1)
            reclen++;
        pos += reclen;
    }
}

void
isofs_dump_directory(uint8_t *buf, int size) {
    directory_record_t rec;

    for (int pos = 0; pos < size;) {
        rec = (directory_record_t)(buf + pos);
        if (rec->dir_rec_len == 0)
            break;

        /* File id */
        isofs_dump_file_id(rec);
        printf(" size %u\r\n", rec->size_le);
        bufdump((char *) rec, rec->dir_rec_len);
#if 0
		/* File creation time and date */
		isofs_dump_record_date(rec);
		printf("\r\n");

		printf("dir_rec_len %u ", rec->dir_rec_len);
		printf("ext_att_rec_len %u ", rec->ext_att_rec_len);
		printf("file_id_len %u\r\n", rec->file_id_len);

		printf("lba %u ", rec->lba_le);
		printf("size %u ", rec->size_le);

		printf("flags 0x%02x ", rec->flags);
		if (rec->flags > 0) {
			printf("(");
			isofs_dump_flags(rec);
			printf(")");
		}
		printf("\r\n");

		printf("unit_size %u ", rec->unit_size);
		printf("interleave_gap_size %u ", rec->interleave_gap_size);
		printf("vol_seqno %u\r\n", rec->vol_seqno_le);
#endif
        pos += rec->dir_rec_len;
    }
}
