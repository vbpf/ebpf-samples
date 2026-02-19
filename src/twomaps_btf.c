// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

// Same as twomaps.c but using BTF-style __type macros for both keys and values.

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, int);
    __type(value, uint64_t);
    __uint(max_entries, 1);
} map1;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, int);
    __type(value, uint64_t);
    __uint(max_entries, 2);
} map2;

struct ctx;

int func(struct ctx* ctx)
{
    uint32_t rand32 = bpf_get_prandom_u32();
    struct ebpf_map* map = (rand32 & 1) ? &map1 : &map2;

    int key = 10;
    uint64_t* value = (uint64_t*)bpf_map_lookup_elem(map, &key);
    if (value == 0)
        return 0;

    // The following is safe since both maps have the same value size.
    return (int)*value;
}
