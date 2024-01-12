// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

typedef struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} inner_map_t;

typedef struct {
    __uint(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
    __uint(max_entries, 1);
    __type(key, uint32_t);
    __array(values, inner_map_t);
} outer_map_t;

__attribute__((section(".maps"), used))
outer_map_t outer_map_1, outer_map_2;


int func(void* ctx) {
    uint32_t outer_key = 0;
    void* inner_map = bpf_map_lookup_elem(&outer_map_1, &outer_key);
    if (inner_map) {
        uint32_t inner_key = 0;
        void* ret = bpf_map_lookup_elem(inner_map, &inner_key);
        if (!ret) {
            return 1;
        }
    }
    inner_map = bpf_map_lookup_elem(&outer_map_2, &outer_key);
    if (inner_map) {
        uint32_t inner_key = 0;
        void* ret = bpf_map_lookup_elem(inner_map, &inner_key);
        if (!ret) {
            return 1;
        }
    }
    return 0;
}
