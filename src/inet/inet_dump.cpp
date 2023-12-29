#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "inet/inet.h"

static const int LEN = 16;

bool dump_enabled = false;

void
bufdump(uint8_t *buf, unsigned len) {
    uint8_t *line;
    int i, j, lines;

    lines = (len + LEN - 1) / LEN;
    for (i = 0; i < lines; i++) {
        line = (uint8_t *) buf + i * LEN;
        for (j = 0; j < LEN; j++) {
            printf("%02x ", line[j]);
            if (j == (LEN / 2) - 1)
                printf(" ");
        }
        printf(" ");
        for (j = 0; j < LEN; j++) {
            if (isprint(line[j]))
                printf("%c", (char) line[j]);
            else
                printf(".");
            if (j == (LEN / 2) - 1)
                printf(" ");
        }
        printf("\r\n");
    }
}

void
dump_ethertype(uint16_t ethertype) {
    switch (ethertype) {
    case ETHERTYPE_IPV4:
        printf("IPv4");
        break;
    case ETHERTYPE_ARP:
        printf("ARP");
        break;
    case ETHERTYPE_RARP:
        printf("RARP");
        break;
    case ETHERTYPE_VLAN:
        printf("802.1Q VLAN");
        break;
    case ETHERTYPE_SNMP:
        printf("SNMP");
        break;
    case ETHERTYPE_IPV6:
        printf("IPv6");
        break;
    case ETHERTYPE_MPLS:
        printf("MPLS");
        break;
    case ETHERTYPE_MPLS_MULTICAST:
        printf("MPLS Multicast");
        break;
    case ETHERTYPE_JUMBO:
        printf("JUMBO");
        break;
    case ETHERTYPE_802_1X:
        printf("802.1X");
        break;
    case ETHERTYPE_802_1AE:
        printf("802.1AE");
        break;
    case ETHERTYPE_PTP:
        printf("PTP");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
}

void
dump_ethaddr(uint8_t *ethaddr) {
    if (ethaddr == NULL)
        return;

    printf("%02x:%02x:%02x:%02x:%02x:%02x", ethaddr[0], ethaddr[1],
           ethaddr[2], ethaddr[3], ethaddr[4], ethaddr[5]);
}

void
dump_ipaddr(uint32_t ipaddr) {
    uint8_t x;

    x = ipaddr >> 24;
    printf("%u.", x);
    x = (ipaddr >> 16) & 0xff;
    printf("%u.", x);
    x = (ipaddr >> 8) & 0xff;
    printf("%u.", x);
    x = ipaddr & 0xff;
    printf("%u", x);
}

void
dump_ipaddr_str(uint32_t ipaddr, char *s) {
    uint8_t x;

    x = ipaddr >> 24;
    sprintf(s, "%u.", x);
    x = (ipaddr >> 16) & 0xff;
    sprintf(s + strlen(s), "%u.", x);
    x = (ipaddr >> 8) & 0xff;
    sprintf(s + strlen(s), "%u.", x);
    x = ipaddr & 0xff;
    sprintf(s + strlen(s), "%u", x);
}

void
dump_ipv6addr(uint8_t *ipv6addr) {
    printf("%02x", ipv6addr[0]);
    for (int i = 1; i < 16; i++) {
        if (i % 2 == 0)
            printf(":");
        printf("%02x", ipv6addr[i]);
    }
}

void
dump_icmp_type(uint8_t icmptype) {
    switch (icmptype) {
    case ICMPTYPE_ECHO_REPLY:
        printf("Echo reply");
        break;
    case ICMPTYPE_DEST_UNREACH:
        printf("Destination unreachable");
        break;
    case ICMPTYPE_SOURCE_QUENCH:
        printf("Source quench");
        break;
    case ICMPTYPE_REDIRECT:
        printf("Redirect");
        break;
    case ICMPTYPE_ALT_HOST_ADDRESS:
        printf("Alternate host address");
        break;
    case ICMPTYPE_ECHO:
        printf("Echo request");
        break;
    case ICMPTYPE_ROUTER_ADVERTISEMENT:
        printf("Router advertisement");
        break;
    case ICMPTYPE_ROUTER_SELECTION:
        printf("Router selection");
        break;
    case ICMPTYPE_TIME_EXCEEDED:
        printf("Time exceeded");
        break;
    case ICMPTYPE_PARAM_PROBLEM:
        printf("Parameter problem");
        break;
    case ICMPTYPE_TIMESTAMP:
        printf("Timestamp request");
        break;
    case ICMPTYPE_TIMESTAMP_REPLY:
        printf("Timestamp reply");
        break;
    case ICMPTYPE_INFO_REQUEST:
        printf("Information request");
        break;
    case ICMPTYPE_INFO_REPLY:
        printf("Information reply");
        break;
    case ICMPTYPE_ADDR_MASK_REQUEST:
        printf("Address mask request");
        break;
    case ICMPTYPE_ADDR_MASK_REPLY:
        printf("Address mask reply");
        break;
    case ICMPTYPE_TRACEROUTE:
        printf("Traceroute");
        break;
    case ICMPTYPE_DGRAM_CONV_ERROR:
        printf("Datagram conversion error");
        break;
    case ICMPTYPE_MOBILE_HOST_REDIRECT:
        printf("Mobile host redirect");
        break;
    case ICMPTYPE_IPV6_WHERE_ARE_YOU:
        printf("IPv6 where are you");
        break;
    case ICMPTYPE_IPV6_I_AM_HERE:
        printf("IPv6 I am here");
        break;
    case ICMPTYPE_MOBILE_REG_REQUEST:
        printf("Mobile registration request");
        break;
    case ICMPTYPE_MOBILE_REG_REPLY:
        printf("Mobile registration reply");
        break;
    case ICMPTYPE_DOMAIN_NAME_REQUEST:
        printf("Domain name request");
        break;
    case ICMPTYPE_DOMAIN_NAME_REPLY:
        printf("Domain name reply");
        break;
    case ICMPTYPE_SKIP:
        printf("Skip");
        break;
    case ICMPTYPE_PHOTURIS:
        printf("Photuris");
        break;
    case ICMPTYPE_EXT_ECHO_REQUEST:
        printf("Extended echo request");
        break;
    case ICMPTYPE_EXT_ECHO_REPLY:
        printf("Extended echo reply");
        break;
    default:
        printf("UNKNOWN");
        break;
    }
}
