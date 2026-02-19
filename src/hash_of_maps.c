// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 4);
} inner_map;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_HASH_OF_MAPS);
    __uint(max_entries, 8);
    __type(key, uint32_t);
    __array(values, inner_map);
} hash_of_maps = {
    .values = { &inner_map },
};

int func(void* ctx) {
    uint32_t outer_key = 0;
    void* inner = bpf_map_lookup_elem(&hash_of_maps, &outer_key);
    if (inner) {
        uint32_t inner_key = 0;
        uint32_t* val = bpf_map_lookup_elem(inner, &inner_key);
        if (val)
            return (int)*val;
    }
    return 0;
}
