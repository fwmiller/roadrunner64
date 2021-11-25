#ifndef __ISO_9660_H
#define __ISO_9660_H

#include <stdint.h>

#define RESERVED_SECTORS	0x10

/* Volume Descriptor types */
#define VOLUME_DESCRIPTOR_TYPE_BOOT_RECORD	0
#define VOLUME_DESCRIPTOR_TYPE_PRIMARY		1
#define VOLUME_DESCRIPTOR_TYPE_SUPPLEMENTARY	2
#define VOLUME_DESCRIPTOR_TYPE_PARTITION	3
#define VOLUME_DESCRIPTOR_TYPE_TERMINATOR	255

struct volume_descriptor {
	uint8_t type;
	uint8_t id[5];
	uint8_t version;
} __attribute__((packed));

struct primary_volume_descriptor {
	uint8_t unused1;
	uint8_t sys_id[32];
	uint8_t vol_id[32];
	uint8_t unused2[8];
	uint32_t vol_space_size_le;
	uint32_t vol_space_size_be;
	uint8_t unused3[32];
	uint16_t vol_set_size_le;
	uint16_t vol_set_size_be;
	uint16_t vol_seqno_le;
	uint16_t vol_seqno_be;
	uint16_t logical_blk_size_le;
	uint16_t logical_blk_size_be;
	uint32_t path_table_size_le;
	uint32_t path_table_size_be;
	uint32_t path_table_loc;
	uint32_t opt_path_table_loc;
	uint8_t root_dir_entry[34];
	uint8_t vol_set_id[128];
	uint8_t publisher_id[128];
	uint8_t data_preparer_id[128];
	uint8_t application_id[128];
	uint8_t copyright_file_id[37];
	uint8_t abstract_file_id[37];
	uint8_t bibliographic_file_id[37];
	uint8_t create_date_time[17];
	uint8_t modify_date_time[17];
	uint8_t expire_date_time[17];
	uint8_t effectiv_date_time[17];
	uint8_t file_structure_version;
	uint8_t unused4;
	uint8_t application[512];
	uint8_t reserved[653];
} __attribute__((packed));

struct path_table_record {
	uint8_t dir_id_len;
	uint8_t ext_att_rec_len;
	uint32_t lba;
	uint16_t parent_dirno;
} __attribute__((packed));

typedef struct volume_descriptor *volume_descriptor_t;
typedef struct primary_volume_descriptor *primary_volume_descriptor_t;
typedef struct path_table_record *path_table_record_t;

#endif
