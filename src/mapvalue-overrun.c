// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, int);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} map;

int func(void* ctx)
{
    uint32_t key = 1;

    uint64_t* ptr = bpf_map_lookup_elem(&map, &key);
    if (ptr == 0) {
        return 0;
    }

    // The map's value size can only hold a uint32_t.
    // So verification should fail if we try to read past the space returned.
    uint64_t i = *ptr;
    return (uint32_t)i;
}
