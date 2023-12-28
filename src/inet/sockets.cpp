#include "inet/sockets.h"
#include <stdlib.h>
#include "inet/udptab.h"

socket::socket(int type) {
    this->type = type;
}

int
socket::bind(uint16_t port) {
    bufq_t q = udptab.alloc_port(port);
    if (q == NULL)
        return (-1);
    this->recvq = q;
    return 0;
}

int
socket::recv(void *buf, unsigned n, int flags) {
    int len = 0;

    if (this->type != SOCK_DGRAM)
        return (-1);

    return len;
}

int
socket::send(void *buf, unsigned n, int flags) {
    int len = 0;

    if (this->type != SOCK_DGRAM)
        return (-1);

    return len;
}
