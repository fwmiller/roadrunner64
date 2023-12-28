#include "inet/stats.h"

class cppip_stats stats;

cppip_stats::cppip_stats() {
    this->frame_count = 0;
}

unsigned
cppip_stats::get_frame_count() {
    return this->frame_count;
}

void
cppip_stats::set_frame_count(unsigned frame_count) {
    this->frame_count = frame_count;
}

void
cppip_stats::inc_frame_count() {
    this->frame_count++;
}

unsigned
cppip_stats::get_eth_count() {
    return this->eth_count;
}

void
cppip_stats::set_eth_count(unsigned eth_count) {
    this->eth_count = eth_count;
}

void
cppip_stats::inc_eth_count() {
    this->eth_count++;
}

unsigned
cppip_stats::get_ieee802_2_count() {
    return this->ieee802_2_count;
}

void
cppip_stats::set_ieee802_2_count(unsigned ieee802_2_count) {
    this->ieee802_2_count = ieee802_2_count;
}

void
cppip_stats::inc_ieee802_2_count() {
    this->ieee802_2_count++;
}

unsigned
cppip_stats::get_arp_count() {
    return this->arp_count;
}

void
cppip_stats::set_arp_count(unsigned arp_count) {
    this->arp_count = arp_count;
}

void
cppip_stats::inc_arp_count() {
    this->arp_count++;
}

unsigned
cppip_stats::get_rarp_count() {
    return this->rarp_count;
}

void
cppip_stats::set_rarp_count(unsigned rarp_count) {
    this->rarp_count = rarp_count;
}

void
cppip_stats::inc_rarp_count() {
    this->rarp_count++;
}

unsigned
cppip_stats::get_ipv4_count() {
    return this->ipv4_count;
}

void
cppip_stats::set_ipv4_count(unsigned ipv4_count) {
    this->ipv4_count = ipv4_count;
}

void
cppip_stats::inc_ipv4_count() {
    this->ipv4_count++;
}

unsigned
cppip_stats::get_ipv6_count() {
    return this->ipv6_count;
}

void
cppip_stats::set_ipv6_count(unsigned ipv6_count) {
    this->ipv6_count = ipv6_count;
}

void
cppip_stats::inc_ipv6_count() {
    this->ipv6_count++;
}

unsigned
cppip_stats::get_icmp_count() {
    return this->icmp_count;
}

void
cppip_stats::set_icmp_count(unsigned icmp_count) {
    this->icmp_count = icmp_count;
}

void
cppip_stats::inc_icmp_count() {
    this->icmp_count++;
}

unsigned
cppip_stats::get_udp_count() {
    return this->udp_count;
}

void
cppip_stats::set_udp_count(unsigned udp_count) {
    this->udp_count = udp_count;
}

void
cppip_stats::inc_udp_count() {
    this->udp_count++;
}

unsigned
cppip_stats::get_tcp_count() {
    return this->tcp_count;
}

void
cppip_stats::set_tcp_count(unsigned tcp_count) {
    this->tcp_count = tcp_count;
}

void
cppip_stats::inc_tcp_count() {
    this->tcp_count++;
}
