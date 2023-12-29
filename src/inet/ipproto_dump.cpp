#include <stdio.h>
#include "inet/inet.h"

void
dump_ipproto(uint8_t proto) {
    switch (proto) {
    case IP_PROTO_HOPOPT:
        printf("IPV6 Hop by Hop");
        break;
    case IP_PROTO_ICMP:
        printf("ICMP");
        break;
    case IP_PROTO_IGMP:
        printf("IGMP");
        break;
    case IP_PROTO_GGP:
        printf("Gateway-to-Gateway Protocol");
        break;
    case IP_PROTO_IP_IN_IP:
        printf("IP in IP Encapsulation");
        break;
    case IP_PROTO_ST:
        printf("Internet Stream Protocol");
        break;
    case IP_PROTO_TCP:
        printf("TCP");
        break;
    case IP_PROTO_CBT:
        printf("Core-based Trees");
        break;
    case IP_PROTO_EGP:
        printf("Exterior Gateway Protocol");
        break;
    case IP_PROTO_IGP:
        printf("Interior Gateway Protocol");
        break;
    case IP_PROTO_BBN_RCC_MON:
        printf("BBN RCC Monitoring");
        break;
    case IP_PROTO_NVP_II:
        printf("Network Voice Protocol");
        break;
    case IP_PROTO_PUP:
        printf("Xerox PUP");
        break;
    case IP_PROTO_ARGUS:
        printf("ARGUS");
        break;
    case IP_PROTO_EMCON:
        printf("EMCON");
        break;
    case IP_PROTO_XNET:
        printf("Cross Net Debugger");
        break;
    case IP_PROTO_CHAOS:
        printf("Chaos");
        break;
    case IP_PROTO_UDP:
        printf("UDP");
        break;
    case IP_PROTO_MUX:
        printf("Multiplexing");
        break;
    case IP_PROTO_DCN_MEAS:
        printf("DCN Measurement Subsystems");
        break;
    case IP_PROTO_HMP:
        printf("Host Monitoring Protocol");
        break;
    case IP_PROTO_PRM:
        printf("Packet Radio Measurement");
        break;
    case IP_PROTO_XMS_IDP:
        printf("Xerox NS IDP");
        break;
    case IP_PROTO_TRUNK_1:
        printf("Trunk-1");
        break;
    case IP_PROTO_TRUNK_2:
        printf("Trunk-2");
        break;
    case IP_PROTO_LEAF_1:
        printf("Leaf-1");
        break;
    case IP_PROTO_LEAF_2:
        printf("Leaf-2");
        break;
    case IP_PROTO_RDP:
        printf("Reliable Data Protocol");
        break;
    case IP_PROTO_IRTP:
        printf("Internet Reliable Transaction Protocol");
        break;
    case IP_PROTO_ISO_TP4:
        printf("ISO TP4");
        break;
    case IP_PROTO_NETBLT:
        printf("Bulk Data Transfer Protocol");
        break;
    case IP_PROTO_MFE_NSP:
        printf("MFE Network Services Protocol");
        break;
    case IP_PROTO_MERIT_INP:
        printf("MERIT Internodal Protocol");
        break;
    case IP_PROTO_DCCP:
        printf("Datagram Congestion Control Protocol");
        break;
    case IP_PROTO_3PC:
        printf("Third Party Connect Protocol");
        break;
    case IP_PROTO_IDPR:
        printf("Inter-Domain Policy Routing Protocol");
        break;
    case IP_PROTO_XTP:
        printf("Xpress Transfer Protocol");
        break;
    case IP_PROTO_DDP:
        printf("Datagram Delivery Protocol");
        break;
    case IP_PROTO_IDPR_CMTP:
        printf("IDPR Control Message Transport Protocol");
        break;
    case IP_PROTO_TPPP:
        printf("TP++ Transport Protocol");
        break;
    case IP_PROTO_IL:
        printf("IL Transport Protocol");
        break;
    case IP_PROTO_IPV6:
        printf("IPV6 Encapsulation");
        break;
    case IP_PROTO_SDRP:
        printf("Source Demand Routing Protocol");
        break;
    case IP_PROTO_IPV6_ROUTE:
        printf("IPV6 Routing");
        break;
    case IP_PROTO_IPV6_FRAG:
        printf("IPV6 Fragment");
        break;
    case IP_PROTO_IDRP:
        printf("Inter-Domain Routing Protocol");
        break;
    case IP_PROTO_RSVP:
        printf("Resource Reservation Protocol");
        break;
    case IP_PROTO_GRES:
        printf("Generic Routing Encapsulation");
        break;
    case IP_PROTO_DSR:
        printf("Dynamic Source Routing Protocol");
        break;
    case IP_PROTO_BNA:
        printf("Burroughs Network Architecture");
        break;
    case IP_PROTO_ESP:
        printf("Encapsulating Security Payload");
        break;
    case IP_PROTO_AH:
        printf("Authentication Header");
        break;
    case IP_PROTO_I_NLSP:
        printf("Integrated Net Layer Security Protocol");
        break;
    case IP_PROTO_SWIPE:
        printf("SwIPe");
        break;
    case IP_PROTO_NARP:
        printf("NBMA ARP");
        break;
    case IP_PROTO_MOBILE:
        printf("IP Mobility");
        break;
    case IP_PROTO_TLSP:
        printf("Transport Layer Security Protocol");
        break;
    case IP_PROTO_SKIP:
        printf("Simple Key-Management for Internet Protocol");
        break;
    case IP_PROTO_IPV6_ICMP:
        printf("IPV6 ICMP");
        break;
    case IP_PROTO_IPV6_NONEXT:
        printf("IPV6 No Next Header");
        break;
    case IP_PROTO_IPV6_OPTS:
        printf("IPV6 Destination Options");
        break;
    case IP_PROTO_ANY_HOST:
        printf("Any host internal protocol");
        break;
    case IP_PROTO_CFTP:
        printf("CFTP");
        break;
    case IP_PROTO_ANY_LOCAL:
        printf("Any local network");
        break;
    case IP_PROTO_SAT_EXPAK:
        printf("SATNET and Backroom EXPAK");
        break;
    case IP_PROTO_KRYPTOLAN:
        printf("Kryptolan");
        break;
    case IP_PROTO_RVD:
        printf("MIT Remote Virtual Disk Protocol");
        break;
    case IP_PROTO_IPPC:
        printf("Internet Pluribus Packet Core");
        break;
    case IP_PROTO_ANY_DIST_FS:
        printf("Any distribute file system");
        break;
    case IP_PROTO_SAT_MON:
        printf("SATNET Monitoring");
        break;
    case IP_PROTO_VISA:
        printf("VISA Protocol");
        break;
    case IP_PROTO_IPCU:
        printf("Internet Packet Core Utility");
        break;
    case IP_PROTO_CPNX:
        printf("Computer Protocol Network Executive");
        break;
    case IP_PROTO_CPHB:
        printf("Computer Protocol Heartbeat");
        break;
    case IP_PROTO_WSN:
        printf("Wang Span Network");
        break;
    case IP_PROTO_PVP:
        printf("Packet Video Protocol");
        break;
    case IP_PROTO_BR_SAT_MON:
        printf("Backroom SATNET Monitoring");
        break;
    case IP_PROTO_SUN_ND:
        printf("SUN ND Protocol");
        break;
    case IP_PROTO_WB_MON:
        printf("WIDEBAND Monitoring");
        break;
    case IP_PROTO_WB_EXPAK:
        printf("WIDEBAND EXPAK");
        break;
    case IP_PROTO_ISO_IP:
        printf("ISO Internet Protocol");
        break;
    case IP_PROTO_VMTP:
        printf("Versatile Message Transaction Protocol");
        break;
    case IP_PROTO_SECURE_VMTP:
        printf("Secure VMTP");
        break;
    case IP_PROTO_VINES:
        printf("VINES");
        break;
    case IP_PROTO_TTP:
        printf("TTP");
        break;
#if 0
	case IP_PROTO_IPTM:
		printf("Internet Protocol Traffic Manager");
		break;
#endif
    case IP_PROTO_NSFNET_IGP:
        printf("NSFNET-IGP");
        break;
    case IP_PROTO_DGP:
        printf("Dissimilar Gateway Protocol");
        break;
    case IP_PROTO_TCF:
        printf("TCF");
        break;
    case IP_PROTO_EIGRP:
        printf("EIGRP");
        break;
    case IP_PROTO_OSPF:
        printf("OSPF");
        break;
    case IP_PROTO_SPRITE_RPC:
        printf("Sprite RPC");
        break;
    case IP_PROTO_LARP:
        printf("Locus Address Resolution Protocol");
        break;
    case IP_PROTO_MTP:
        printf("Multicast Transport Protocol");
        break;
    case IP_PROTO_AX_25:
        printf("AX.25");
        break;
    case IP_PROTO_KA9Q_IP_TUNNEL:
        printf("KA9Q IP tunneling");
        break;
    case IP_PROTO_MICP:
        printf("Mobile Internetworking Control Protocol");
        break;
    case IP_PROTO_SCC_SP:
        printf("Semaphore Comm Sec Pro");
        break;
    case IP_PROTO_ETHERIP:
        printf("Ethernet-in-IP Encapsulation");
        break;
    case IP_PROTO_ENCAP:
        printf("Encapsulation Header");
        break;
    case IP_PROTO_ANY_PVT_ENCRYPTION:
        printf("Any private encryption");
        break;
    case IP_PROTO_GMTP:
        printf("GMTP");
        break;
    case IP_PROTO_IFMP:
        printf("Ipsilon Flow Mgmt Protocol");
        break;
    case IP_PROTO_PNNI:
        printf("PNNI over IP");
        break;
    case IP_PROTO_PIM:
        printf("Protocol Independent Broadcast");
        break;
    case IP_PROTO_ARIS:
        printf("IBM ARIS");
        break;
    case IP_PROTO_SCPS:
        printf("Space Communications Protocol Standard");
        break;
    case IP_PROTO_QNX:
        printf("QNX");
        break;
    case IP_PROTO_A_N:
        printf("Active Networks");
        break;
    case IP_PROTO_IPCOMP:
        printf("IP Payload Compression Protocol");
        break;
    case IP_PROTO_SNP:
        printf("Sitara Networks Protocol");
        break;
    case IP_PROTO_COMPAQ_PEER:
        printf("Compaq Peer Protocol");
        break;
    case IP_PROTO_IPX_IN_IP:
        printf("IPX in IP");
        break;
    case IP_PROTO_VRRP:
        printf("Virtual Router Redundancy Protocol");
        break;
    case IP_PROTO_PGM:
        printf("PGM Reliable Transport Protocol");
        break;
    case IP_PROTO_ANY_ZERO_HOP:
        printf("Any 0-hop protocol");
        break;
    case IP_PROTO_L2TP:
        printf("Layer 2 Tunneling");
        break;
    case IP_PROTO_DDX:
        printf("D-II Data Exchange");
        break;
    case IP_PROTO_IATP:
        printf("Interactive Agent Transfer Protocol");
        break;
    case IP_PROTO_STP:
        printf("Schedule Transfer Protocol");
        break;
    case IP_PROTO_SRP:
        printf("SpectraLink Radio Protocol");
        break;
    case IP_PROTO_UTI:
        printf("Universal Transport Interface");
        break;
    case IP_PROTO_SMP:
        printf("Simple Message Protocol");
        break;
    case IP_PROTO_SM:
        printf("Simple Multicast Protocol");
        break;
    case IP_PROTO_PTP:
        printf("Performance Transparency Protocol");
        break;
    case IP_PROTO_IS_IS:
        printf("IS-IS over IPv4");
        break;
    case IP_PROTO_FIRE:
        printf("Flexible Intra-AS Routing Environment");
        break;
    case IP_PROTO_CRTP:
        printf("Combat Radio Transport");
        break;
    case IP_PROTO_CRUDP:
        printf("Combat Radio User Datagram");
        break;
    case IP_PROTO_SSCOPMCE:
        printf("SSCOPME");
        break;
    case IP_PROTO_IPLT:
        printf("IPLT");
        break;
    case IP_PROTO_SPS:
        printf("Secure Packet Shield");
        break;
    case IP_PROTO_PIPE:
        printf("Private IP Encapsulation in IP");
        break;
    case IP_PROTO_SCTP:
        printf("Stream Control Transmission Protocol");
        break;
    case IP_PROTO_FC:
        printf("Fibre Channel");
        break;
    case IP_PROTO_RSVP_E2E_IGNORE:
        printf("RSVP E2E Ignore");
        break;
    case IP_PROTO_MOBILITY_HDR:
        printf("Mobility Ext Hdr for IPv6");
        break;
    case IP_PROTO_UDP_LITE:
        printf("Lightweight UDP");
        break;
    case IP_PROTO_MPLS_IN_IP:
        printf("MPLS in IP");
        break;
    case IP_PROTO_MANET:
        printf("Mobile Ad-Hoc Network Protocol");
        break;
    case IP_PROTO_HIP:
        printf("Host Identity Protocol");
        break;
    case IP_PROTO_SHIM6:
        printf("Site Multi-homing by IPv6");
        break;
    case IP_PROTO_WESP:
        printf("Wrapped Encapsulating Security Payload");
        break;
    case IP_PROTO_ROHC:
        printf("Robust Header Compression");
        break;
    case IP_PROTO_ETHERNET:
        printf("IPv6 Segment Routing");
        break;
    case IP_PROTO_EXPERIMENTAL_1:
        printf("Experimental");
        break;
    case IP_PROTO_EXPERIMENTAL_2:
        printf("Experimental");
        break;
    case IP_PROTO_RESERVED:
        printf("Reserved");
        break;
    default:
        printf("Unassigned");
        break;
    }
}
