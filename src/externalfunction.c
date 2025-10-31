// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

// Override bpf_map_lookup_elem in the header to test external function resolution.
#define bpf_map_lookup_elem external_bpf_map_lookup_elem
#include "bpf.h"
#undef bpf_map_lookup_elem

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} test_map;

// Helper function that will be resolved by name by the eBPF loader (instead of by helper id).
extern void* bpf_map_lookup_elem(void *map, const void *key);

struct ctx;

int func(struct ctx* ctx)
{
    uint32_t key = 0;
    void* val = bpf_map_lookup_elem(&test_map, &key);
    if (val) {
        return 0;
    }
    return 1;    
}
