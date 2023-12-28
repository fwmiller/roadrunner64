#include "inet/ports.h"
#include <stdlib.h>
#include <string.h>
#include "inet/udptab.h"

port::port() {
    return;
}

int
port::bind(uint16_t portnum) {
    bufq_t q;

    q = udptab.find_port(portnum);
    if (q != NULL)
        return (-1);

    q = udptab.alloc_port(portnum);
    if (q == NULL)
        return (-1);
    this->receiveq = q;
    return 0;
}

int
port::get_nbufs() {
    if (this->receiveq != NULL)
        return this->receiveq->get_nbufs();
    return (-1);
}

int
port::get_length() {
    if (this->receiveq != NULL)
        return this->receiveq->get_length();
    return (-1);
}

int
port::receive(void *buf, unsigned bufsize) {
    if (this->receiveq == NULL)
        return (-1);

    // Remove packet buffer from queue
    int len = 0;
    buf_t b = this->receiveq->remove(&len);
    if (b == NULL)
        return (-1);

    // Copy packet buffer data into parameter buffer
    memcpy(buf, b, (bufsize > (unsigned) len ? len : bufsize));

    // ??? Free packet buffer

    return len;
}

int
port::send(void *buf, unsigned len) {
    return (-1);
}
