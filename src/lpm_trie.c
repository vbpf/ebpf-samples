// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

struct lpm_key {
    uint32_t prefixlen;
    uint32_t data;
};

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_LPM_TRIE);
    __type(key, struct lpm_key);
    __type(value, uint64_t);
    __uint(max_entries, 256);
    __uint(map_flags, 1); /* BPF_F_NO_PREALLOC */
} lpm_map;

__attribute__((section("xdp"), used))
int test_lpm_trie(struct xdp_md* ctx)
{
    struct lpm_key key = {
        .prefixlen = 24,
        .data = 0x0a000000, /* 10.0.0.0/24 */
    };

    uint64_t* value = bpf_map_lookup_elem(&lpm_map, &key);
    if (value)
        return (int)*value;

    uint64_t new_val = 1;
    bpf_map_update_elem(&lpm_map, &key, &new_val, 0);
    return 0;
}
