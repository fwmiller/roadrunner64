#ifndef __CPPIP
#define __CPPIP

#include <stdint.h>

static const unsigned ETH_ADDR_LEN = 6;
static const unsigned IPV4_ADDR_LEN = 4;

typedef uint8_t *buf_t;

extern bool dump_enabled;

#include "inet/arp.h"
#include "inet/buf.h"
#include "inet/eth.h"
#include "inet/ethertype.h"
#include "inet/icmp.h"
#include "inet/icmpv6.h"
#include "inet/ieee802_2.h"
#include "inet/ipproto.h"
#include "inet/ipv4.h"
#include "inet/ipv6.h"
#include "inet/udp.h"

extern char intf_name[];
extern bufpool_t bp;

void inet_init();

//
// Utilities
//
void bufdump(uint8_t *buf, unsigned len);
void dump_ethertype(uint16_t ethertype);
void dump_ethaddr(uint8_t *ethaddr);
void dump_ipproto(uint8_t proto);
void dump_ipaddr(uint32_t ipaddr);
void dump_ipv6addr(uint8_t *ipv6addr);
void dump_icmp_type(uint8_t icmptype);

void dump_ipaddr_str(uint32_t ipaddr, char *s);

uint16_t reverse_byte_order_short(uint16_t x);
uint32_t reverse_byte_order_long(uint32_t x);

#endif
