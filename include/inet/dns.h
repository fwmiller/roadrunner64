#ifndef __DNS_H
#define __DNS_H

#include "cppip.h"

struct dns_hdr {
    uint16_t id;
    uint16_t op;
    uint16_t qdcount;
    uint16_t ancount;
    uint16_t nscount;
    uint16_t arcount;
} __attribute__((packed));

typedef struct dns_hdr *dns_hdr_t;

#endif
