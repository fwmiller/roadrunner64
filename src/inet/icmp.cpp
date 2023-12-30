#include "inet/icmp.h"
#include <stdlib.h>

icmp::icmp() {
    return;
}

buf_t
icmp::get_buf() {
    return this->buf;
}

void
icmp::set_buf(buf_t buf) {
    this->buf = buf;
}

void
icmp::receive() {
#if _DEBUG_INET
    this->dump();
#endif
}
