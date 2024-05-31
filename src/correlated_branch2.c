// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

typedef struct _ETHERNET_HEADER {
    unsigned char Destination[6];
    unsigned char Source[6];
    union {
        unsigned short Type;   // Ethernet
        unsigned short Length; // IEEE 802
    };
} ETHERNET_HEADER, *PETHERNET_HEADER;

typedef uint8_t ipv6_address_t[16];

typedef struct _IPV6_HEADER {
    union {
        uint32_t VersionClassFlow; // 4 bits Version, 8 Traffic Class, 20 Flow Label.
        struct {                   // Convenience structure to access Version field only.
            uint32_t : 4;
            uint32_t Version : 4;
            uint32_t : 24;
        };
    };
    uint16_t PayloadLength; // Zero indicates Jumbo Payload hop-by-hop option.
    uint8_t NextHeader;     // Values are superset of IPv4's Protocol field.
    uint8_t HopLimit;
    ipv6_address_t SourceAddress;
    ipv6_address_t DestinationAddress;
} IPV6_HEADER, *PIPV6_HEADER;

enum {
    DROP_NOT_ETHERNET = -1,
    DROP_WRONG_ETHERNET_TYPE = -2,
    DROP_NOT_IPV6 = -3,
    DROP_INVALID = -4,
    DROP_FAILED_TO_STORE = -5
} eBPF_DROP_REASON;

// This program is a socket filter that swaps the source and destination IPv6 addresses of an IPv6 packet.
// If the packet is not an ethernet packet, it is dropped with DROP_NOT_ETHERNET.
// If the packet has the wrong ethernet type, it is dropped with DROP_WRONG_ETHERNET_TYPE.
// If the packet is not an IPv6 packet, it is dropped with DROP_NOT_IPV6.
// If the packet is an IPv6 packet with a version other than 6, it is dropped with DROP_INVALID.
// If the packet is an IPv6 packet with version 6, the source and destination addresses are swapped.
SEC("socket_filter")
int ConvergedBranch(struct __sk_buff* ctx) {
    ETHERNET_HEADER ethhdr;
    IPV6_HEADER ip6hdr;
    int return_value = 0;

    if (bpf_skb_load_bytes(ctx, 0, &ethhdr, sizeof(ethhdr)) < 0) {
        return_value = DROP_NOT_ETHERNET;
    }

    if (return_value == 0 && ethhdr.Type != 0x0806) {
        return_value = DROP_WRONG_ETHERNET_TYPE;
    }

    if (return_value == 0 && bpf_skb_load_bytes(ctx, sizeof(ETHERNET_HEADER), &ip6hdr, sizeof(ip6hdr)) < 0) {
        return_value = DROP_NOT_IPV6;
    }

    if (return_value == 0 && ip6hdr.Version == 6) {
        return_value = DROP_INVALID;
    }

    if (return_value == 0) {
        ipv6_address_t temp;
        __builtin_memcpy(temp, ip6hdr.SourceAddress, sizeof(ip6hdr.SourceAddress));
        __builtin_memcpy(ip6hdr.SourceAddress, ip6hdr.DestinationAddress, sizeof(ip6hdr.DestinationAddress));
        __builtin_memcpy(ip6hdr.DestinationAddress, temp, sizeof(ip6hdr.DestinationAddress));
    }

    if (return_value == 0 && bpf_skb_store_bytes(ctx, sizeof(ETHERNET_HEADER), &ip6hdr, sizeof(ip6hdr), 0) < 0) {
        return_value = DROP_FAILED_TO_STORE;
    }

    return return_value;
}
