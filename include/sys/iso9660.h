#ifndef __ISO_9660_H
#define __ISO_9660_H

#include <stdint.h>

/* Volume Descriptor types */
const int VOLUME_DESCRIPTOR_TYPE_BOOT_RECORD   = 0;
const int VOLUME_DESCRIPTOR_TYPE_PRIMARY       = 1;
const int VOLUME_DESCRIPTOR_TYPE_SUPPLEMENTARY = 2;
const int VOLUME_DESCRIPTOR_TYPE_PARTITION     = 3;
const int VOLUME_DESCRIPTOR_TYPE_TERMINATOR    = 255;

struct volume_descriptor {
	uint8_t type;
	uint8_t id[5];
	uint8_t version;
};

#endif
