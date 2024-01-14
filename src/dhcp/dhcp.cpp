#include "inet/dhcp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "inet/inet.h"
#include "inet/ports.h"

void *
dhcp(void *pthread_arg) {
    class port dhcp_server;
    class port dhcp_client;
    uint8_t buf[ETH_MTU_SIZE];
    int len, n;

    dhcp_server.bind(DHCP_PORT_SERVER);
    dhcp_client.bind(DHCP_PORT_CLIENT);

    for (;;) {
        n = dhcp_server.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_server.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;
#if _DEBUG_DHCP
            printf("dhcp server ");
            dhcp_dump(buf, len);
#endif
        }
        n = dhcp_client.get_nbufs();
        while (n > 0) {
            memset(buf, 0, ETH_MTU_SIZE);
            len = dhcp_client.receive(buf, ETH_MTU_SIZE);
            if (len < 0)
                break;
#if _DEBUG_DHCP
            printf("dhcp client ");
            dhcp_dump(buf, len);
#endif
        }
        // usleep(20000);  // 20 milliseconds
    }

    /* Not reached */
    return NULL;
}
