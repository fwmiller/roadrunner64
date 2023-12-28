#ifndef __IP_PROTOCOL
#define __IP_PROTOCOL

#include <stdint.h>

static const uint8_t IP_PROTO_HOPOPT = 0;
static const uint8_t IP_PROTO_ICMP = 0x01;
static const uint8_t IP_PROTO_IGMP = 0x02;
static const uint8_t IP_PROTO_GGP = 0x03;
static const uint8_t IP_PROTO_IP_IN_IP = 0x04;
static const uint8_t IP_PROTO_ST = 0x05;
static const uint8_t IP_PROTO_TCP = 0x06;
static const uint8_t IP_PROTO_CBT = 0x07;
static const uint8_t IP_PROTO_EGP = 0x08;
static const uint8_t IP_PROTO_IGP = 0x09;
static const uint8_t IP_PROTO_BBN_RCC_MON = 0x0a;
static const uint8_t IP_PROTO_NVP_II = 0x0b;
static const uint8_t IP_PROTO_PUP = 0x0c;
static const uint8_t IP_PROTO_ARGUS = 0x0d;
static const uint8_t IP_PROTO_EMCON = 0x0e;
static const uint8_t IP_PROTO_XNET = 0x0f;
static const uint8_t IP_PROTO_CHAOS = 0x10;
static const uint8_t IP_PROTO_UDP = 0x11;
static const uint8_t IP_PROTO_MUX = 0x12;
static const uint8_t IP_PROTO_DCN_MEAS = 0x13;
static const uint8_t IP_PROTO_HMP = 0x14;
static const uint8_t IP_PROTO_PRM = 0x15;
static const uint8_t IP_PROTO_XMS_IDP = 0x16;
static const uint8_t IP_PROTO_TRUNK_1 = 0x17;
static const uint8_t IP_PROTO_TRUNK_2 = 0x18;
static const uint8_t IP_PROTO_LEAF_1 = 0x19;
static const uint8_t IP_PROTO_LEAF_2 = 0x1a;
static const uint8_t IP_PROTO_RDP = 0x1b;
static const uint8_t IP_PROTO_IRTP = 0x1c;
static const uint8_t IP_PROTO_ISO_TP4 = 0x1d;
static const uint8_t IP_PROTO_NETBLT = 0x1e;
static const uint8_t IP_PROTO_MFE_NSP = 0x1f;
static const uint8_t IP_PROTO_MERIT_INP = 0x20;
static const uint8_t IP_PROTO_DCCP = 0x21;
static const uint8_t IP_PROTO_3PC = 0x22;
static const uint8_t IP_PROTO_IDPR = 0x23;
static const uint8_t IP_PROTO_XTP = 0x24;
static const uint8_t IP_PROTO_DDP = 0x25;
static const uint8_t IP_PROTO_IDPR_CMTP = 0x26;
static const uint8_t IP_PROTO_TPPP = 0x27;
static const uint8_t IP_PROTO_IL = 0x28;
static const uint8_t IP_PROTO_IPV6 = 0x29;
static const uint8_t IP_PROTO_SDRP = 0x2a;
static const uint8_t IP_PROTO_IPV6_ROUTE = 0x2b;
static const uint8_t IP_PROTO_IPV6_FRAG = 0x2c;
static const uint8_t IP_PROTO_IDRP = 0x2d;
static const uint8_t IP_PROTO_RSVP = 0x2e;
static const uint8_t IP_PROTO_GRES = 0x2f;
static const uint8_t IP_PROTO_DSR = 0x30;
static const uint8_t IP_PROTO_BNA = 0x31;
static const uint8_t IP_PROTO_ESP = 0x32;
static const uint8_t IP_PROTO_AH = 0x33;
static const uint8_t IP_PROTO_I_NLSP = 0x34;
static const uint8_t IP_PROTO_SWIPE = 0x35;
static const uint8_t IP_PROTO_NARP = 0x36;
static const uint8_t IP_PROTO_MOBILE = 0x37;
static const uint8_t IP_PROTO_TLSP = 0x38;
static const uint8_t IP_PROTO_SKIP = 0x39;
static const uint8_t IP_PROTO_IPV6_ICMP = 0x3a;
static const uint8_t IP_PROTO_IPV6_NONEXT = 0x3b;
static const uint8_t IP_PROTO_IPV6_OPTS = 0x3c;
static const uint8_t IP_PROTO_ANY_HOST = 0x3d;
static const uint8_t IP_PROTO_CFTP = 0x3e;
static const uint8_t IP_PROTO_ANY_LOCAL = 0x3f;
static const uint8_t IP_PROTO_SAT_EXPAK = 0x40;
static const uint8_t IP_PROTO_KRYPTOLAN = 0x41;
static const uint8_t IP_PROTO_RVD = 0x42;
static const uint8_t IP_PROTO_IPPC = 0x43;
static const uint8_t IP_PROTO_ANY_DIST_FS = 0x44;
static const uint8_t IP_PROTO_SAT_MON = 0x45;
static const uint8_t IP_PROTO_VISA = 0x46;
static const uint8_t IP_PROTO_IPCU = 0x47;
static const uint8_t IP_PROTO_CPNX = 0x48;
static const uint8_t IP_PROTO_CPHB = 0x49;
static const uint8_t IP_PROTO_WSN = 0x4a;
static const uint8_t IP_PROTO_PVP = 0x4b;
static const uint8_t IP_PROTO_BR_SAT_MON = 0x4c;
static const uint8_t IP_PROTO_SUN_ND = 0x4d;
static const uint8_t IP_PROTO_WB_MON = 0x4e;
static const uint8_t IP_PROTO_WB_EXPAK = 0x4f;
static const uint8_t IP_PROTO_ISO_IP = 0x50;
static const uint8_t IP_PROTO_VMTP = 0x51;
static const uint8_t IP_PROTO_SECURE_VMTP = 0x52;
static const uint8_t IP_PROTO_VINES = 0x53;
static const uint8_t IP_PROTO_TTP = 0x54;
static const uint8_t IP_PROTO_IPTM = 0x54;
static const uint8_t IP_PROTO_NSFNET_IGP = 0x55;
static const uint8_t IP_PROTO_DGP = 0x56;
static const uint8_t IP_PROTO_TCF = 0x57;
static const uint8_t IP_PROTO_EIGRP = 0x58;
static const uint8_t IP_PROTO_OSPF = 0x59;
static const uint8_t IP_PROTO_SPRITE_RPC = 0x5a;
static const uint8_t IP_PROTO_LARP = 0x5b;
static const uint8_t IP_PROTO_MTP = 0x5c;
static const uint8_t IP_PROTO_AX_25 = 0x5d;
static const uint8_t IP_PROTO_KA9Q_IP_TUNNEL = 0x5e;
static const uint8_t IP_PROTO_MICP = 0x5f;
static const uint8_t IP_PROTO_SCC_SP = 0x60;
static const uint8_t IP_PROTO_ETHERIP = 0x61;
static const uint8_t IP_PROTO_ENCAP = 0x62;
static const uint8_t IP_PROTO_ANY_PVT_ENCRYPTION = 0x63;
static const uint8_t IP_PROTO_GMTP = 0x64;
static const uint8_t IP_PROTO_IFMP = 0x65;
static const uint8_t IP_PROTO_PNNI = 0x66;
static const uint8_t IP_PROTO_PIM = 0x67;
static const uint8_t IP_PROTO_ARIS = 0x68;
static const uint8_t IP_PROTO_SCPS = 0x69;
static const uint8_t IP_PROTO_QNX = 0x6a;
static const uint8_t IP_PROTO_A_N = 0x6b;
static const uint8_t IP_PROTO_IPCOMP = 0x6c;
static const uint8_t IP_PROTO_SNP = 0x6d;
static const uint8_t IP_PROTO_COMPAQ_PEER = 0x6e;
static const uint8_t IP_PROTO_IPX_IN_IP = 0x6f;
static const uint8_t IP_PROTO_VRRP = 0x70;
static const uint8_t IP_PROTO_PGM = 0x71;
static const uint8_t IP_PROTO_ANY_ZERO_HOP = 0x72;
static const uint8_t IP_PROTO_L2TP = 0x73;
static const uint8_t IP_PROTO_DDX = 0x74;
static const uint8_t IP_PROTO_IATP = 0x75;
static const uint8_t IP_PROTO_STP = 0x76;
static const uint8_t IP_PROTO_SRP = 0x77;
static const uint8_t IP_PROTO_UTI = 0x78;
static const uint8_t IP_PROTO_SMP = 0x79;
static const uint8_t IP_PROTO_SM = 0x7a;
static const uint8_t IP_PROTO_PTP = 0x7b;
static const uint8_t IP_PROTO_IS_IS = 0x7c;
static const uint8_t IP_PROTO_FIRE = 0x7d;
static const uint8_t IP_PROTO_CRTP = 0x7e;
static const uint8_t IP_PROTO_CRUDP = 0x7f;
static const uint8_t IP_PROTO_SSCOPMCE = 0x80;
static const uint8_t IP_PROTO_IPLT = 0x81;
static const uint8_t IP_PROTO_SPS = 0x82;
static const uint8_t IP_PROTO_PIPE = 0x83;
static const uint8_t IP_PROTO_SCTP = 0x84;
static const uint8_t IP_PROTO_FC = 0x85;
static const uint8_t IP_PROTO_RSVP_E2E_IGNORE = 0x86;
static const uint8_t IP_PROTO_MOBILITY_HDR = 0x87;
static const uint8_t IP_PROTO_UDP_LITE = 0x88;
static const uint8_t IP_PROTO_MPLS_IN_IP = 0x89;
static const uint8_t IP_PROTO_MANET = 0x8a;
static const uint8_t IP_PROTO_HIP = 0x8b;
static const uint8_t IP_PROTO_SHIM6 = 0x8c;
static const uint8_t IP_PROTO_WESP = 0x8d;
static const uint8_t IP_PROTO_ROHC = 0x8e;
static const uint8_t IP_PROTO_ETHERNET = 0x8f;
static const uint8_t IP_PROTO_EXPERIMENTAL_1 = 0xfd;
static const uint8_t IP_PROTO_EXPERIMENTAL_2 = 0xfe;
static const uint8_t IP_PROTO_RESERVED = 0xff;

#endif
