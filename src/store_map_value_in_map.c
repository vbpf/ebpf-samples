// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} map1;


__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} map2;

int func(void* ctx) {
    // Lookup value from map1 and store it in map 2.
    uint32_t key = 0;
    uint32_t *val = bpf_map_lookup_elem(&map1, &key);
    if (val) {
        if (bpf_map_update_elem(&map2, &key, val, 0)) {
            return 1;
        }
    }
    return 0;
}
