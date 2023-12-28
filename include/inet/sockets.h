#ifndef __SOCKETS_H
#define __SOCKETS_H

#include <stdint.h>
#include "buf.h"

// These should be non-zero
static const int SOCK_DGRAM = 1;

class socket {
private:
    int type;
    bufq_t recvq;

public:
    socket(int type);
    int bind(uint16_t port);

    int recv(void *buf, unsigned n, int flags);
    int send(void *buf, unsigned n, int flags);
};

#endif
