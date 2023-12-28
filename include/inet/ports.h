#ifndef __PORTS_H
#define __PORTS_H

#include <stdint.h>
#include "buf.h"

class port {
private:
    bufq_t receiveq;

public:
    port();

    // Bind portnum to this port
    int bind(uint16_t portnum);

    // Return the number of buffers in the queue
    int get_nbufs();

    // Return the length in bytes of data in the port receive queue
    int get_length();

    // Remove up to bufsize bytes from the port receive queue and
    // copy them into buf.  Each receive call returns the data from
    // one received UDP datagram.
    int receive(void *buf, unsigned bufsize);

    // Send len bytes located at buf to the network from this portnum
    int send(void *buf, unsigned len);
};

#endif
