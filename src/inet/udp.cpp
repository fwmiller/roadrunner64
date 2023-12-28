#include "inet/udp.h"
#include <stdlib.h>

udp::udp() {
    this->buf = NULL;
}

buf_t
udp::get_buf() {
    return this->buf;
}

void
udp::set_buf(buf_t buf) {
    this->buf = buf;
}
