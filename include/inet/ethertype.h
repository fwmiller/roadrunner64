#ifndef __ETHERTYPE_H
#define __ETHERTYPE_H

#include <stdint.h>

static const uint16_t ETHERTYPE_IPV4 = 0x0800;
static const uint16_t ETHERTYPE_ARP = 0x0806;
static const uint16_t ETHERTYPE_RARP = 0x8035;
static const uint16_t ETHERTYPE_VLAN = 0x8100;
static const uint16_t ETHERTYPE_SNMP = 0x814c;
static const uint16_t ETHERTYPE_IPV6 = 0x86dd;
static const uint16_t ETHERTYPE_MPLS = 0x8847;
static const uint16_t ETHERTYPE_MPLS_MULTICAST = 0x8848;
static const uint16_t ETHERTYPE_JUMBO = 0x8870;
static const uint16_t ETHERTYPE_802_1X = 0x888e;
static const uint16_t ETHERTYPE_802_1AE = 0x88e5;
static const uint16_t ETHERTYPE_PTP = 0x88f7;

#endif
