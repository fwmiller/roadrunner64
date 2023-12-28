#ifndef __DHCP_H
#define __DHCP_H

#include <stdint.h>

#define DHCP_PORT_SERVER 67
#define DHCP_PORT_CLIENT 68

#define DHCP_OPT_PAD 0
#define DHCP_OPT_SUBNET_MASK 1
#define DHCP_OPT_TIME_OFFSET 2
#define DHCP_OPT_ROUTER 3
#define DHCP_OPT_TIME_SERVER 4
#define DHCP_OPT_NAME_SERVER 5
#define DHCP_OPT_DOMAIN_NAME_SERVER 6
#define DHCP_OPT_LOG_SERVER 7
#define DHCP_OPT_COOKIE_SERVER 8
#define DHCP_OPT_LPR_SERVER 9
#define DHCP_OPT_IMPRESS_SERVER 10
#define DHCP_OPT_RESOURCE_LOCATION_SERVER 11
#define DHCP_OPT_HOST_NAME 12
#define DHCP_OPT_BOOT_FILE_SIZE 13
#define DHCP_OPT_MERIT_DUMP_FILE 14
#define DHCP_OPT_DOMAIN_NAME 15
#define DHCP_OPT_SWAP_SERVER 16
#define DHCP_OPT_ROOT_PATH 17
#define DHCP_OPT_EXTENSIONS_PATH 18

#define DHCP_OPT_REQUESTED_IP_ADDR 50
#define DHCP_OPT_IP_ADDR_LEASE_TIME 51
#define DHCP_OPT_OVERLOAD 52
#define DHCP_OPT_MESSAGE_TYPE 53
#define DHCP_OPT_SERVER_ID 54
#define DHCP_OPT_PARAMETER_REQ_LIST 55
#define DHCP_OPT_MESSAGE 56
#define DHCP_OPT_MAX_DHCP_MSG_SIZE 57
#define DHCP_OPT_RENEWAL 58
#define DHCP_OPT_REBINDING 59
#define DHCP_OPT_VENDOR_CLASS_ID 60
#define DHCP_OPT_CLIENT_ID 61
#define DHCP_OPT_TFTP_SERVER_NAME 66
#define DHCP_OPT_BOOTFILE_NAME 67

#define DHCP_OPT_END 255

/* DHCP option message types */
#define DHCPDISCOVER 1
#define DHCPOFFER 2
#define DHCPREQUEST 3
#define DHCPDECLINE 4
#define DHCPACK 5
#define DHCPNAK 6
#define DHCPRELEASE 7
#define DHCPINFORM 8
#define DHCPFORCERENEW 9
#define DHCPLEASEQUERY 10
#define DHCPLEASEUNASSIGNED 11
#define DHCPLEASEUNKNOWN 12
#define DHCPLEASEACTIVE 13
#define DHCPBULKLEASEQUERY 14
#define DHCPLEASEQUERYDONE 15
#define DHCPACTIVELEASEQUERY 16
#define DHCPLEASEQUERYSTATUS 17
#define DHCPTLS 18

struct dhcp_hdr {
    uint8_t op;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint16_t flags;
    uint32_t ciaddr;
    uint32_t yiaddr;
    uint32_t siaddr;
    uint32_t giaddr;
    uint8_t chaddr[16];
    uint8_t sname[64];
    uint8_t file[128];
    uint32_t cookie;
} __attribute__((packed));

typedef struct dhcp_hdr *dhcp_hdr_t;

void dhcp_dump(uint8_t *buf, int buflen);
void *dhcp(void *pthread_arg);

#endif
