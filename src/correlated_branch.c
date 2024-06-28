// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

#if defined(PASS)
typedef volatile struct xdp_md xdp_md_t;
#else
typedef struct xdp_md xdp_md_t;
#endif // PASS

struct
{
    __uint(type, 1);
    __type(key, unsigned int);
    __uint(value_size, 16);
    __uint(max_entries, 1);
} test_map SEC(".maps");

typedef struct _ETHERNET_HEADER
{
    unsigned char Destination[6];
    unsigned char Source[6];
    union
    {
        unsigned short Type;   // Ethernet
        unsigned short Length; // IEEE 802
    };
} ETHERNET_HEADER, *PETHERNET_HEADER;


__attribute__((always_inline)) static inline void *check_packet(xdp_md_t *ctx, long required_length)
{
    void* data_start = (void *)(uintptr_t)ctx->data;
    void* data_end = (void *)(uintptr_t)ctx->data_end;
    if ((data_end - data_start) < required_length)
    {
        return 0;
    }
    return (void *)(uintptr_t)ctx->data;
}

__attribute__((always_inline)) static inline char add_type_to_test_map(xdp_md_t *ctx, unsigned long *value)
{
    ETHERNET_HEADER *ethernet_header;
    ethernet_header = check_packet(ctx, sizeof(ETHERNET_HEADER));
    if (ethernet_header && ethernet_header->Type == 0x0800)
    {
        (*value)++;
        return 1;
    }
    else if (ethernet_header && ethernet_header->Type == 0x0806)
    {
        (*value)++;
        return 1;
    }
    {
        return 0;
    }
}

SEC("xdp")
int ConvergedBranch(xdp_md_t *ctx)
{
    unsigned long key = 0;
    unsigned long *value = bpf_map_lookup_elem(&test_map, &key);
    ETHERNET_HEADER *header = check_packet(ctx, sizeof(ETHERNET_HEADER));


    if (header == NULL)
    {
        goto Exit;
    }

    if (!value)
    {
        goto Exit;
    }

    if (header->Type == 0x0800 || header->Type == 0x0806) {
        if (!add_type_to_test_map(ctx, value))
        {
            goto Exit;
        }
    }

Exit:
    return 0;
}
