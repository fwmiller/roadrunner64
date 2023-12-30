#include "inet/arp.h"
#include <stdlib.h>
#include <string.h>

arp::arp() {
    this->buf = NULL;
    this->hdr = NULL;
}

buf_t
arp::get_buf() {
    return this->buf;
}

void
arp::set_buf(buf_t buf) {
    this->buf = buf;
}

uint8_t *
arp::get_hdr() {
    return this->hdr;
}

void
arp::set_hdr(uint8_t *hdr) {
    this->hdr = hdr;
}

void
arp::generate(uint8_t *hdr, uint16_t hw, uint16_t proto, uint8_t hw_addr_len,
              uint8_t proto_addr_len, uint16_t opcode, uint8_t *sha,
              uint32_t spa, uint8_t *tha, uint32_t tpa) {
    arp_hdr_t ah = (arp_hdr_t) hdr;
    ah->hw = reverse_byte_order_short(hw);
    ah->proto = reverse_byte_order_short(proto);
    ah->hw_addr_len = hw_addr_len;
    ah->proto_addr_len = proto_addr_len;
    ah->opcode = reverse_byte_order_short(opcode);
    if (sha != NULL)
        memcpy(ah->sha, sha, ETH_ADDR_LEN);
    ah->spa = spa;
    if (tha != NULL)
        memcpy(ah->tha, tha, ETH_ADDR_LEN);
    ah->tpa = tpa;
}
