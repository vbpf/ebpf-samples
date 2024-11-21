// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_RINGBUF);
    __uint(max_entries, 256 * 1024);
} inner_map;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY_OF_MAPS);
    __uint(max_entries, 1);
    __type(key, uint32_t);
    __array(values, inner_map);
} array_of_maps = {
    .values = { &inner_map },
};

int func(void* ctx) {
    uint32_t outer_key = 0;
    void* nolocal_lru_map = bpf_map_lookup_elem(&array_of_maps, &outer_key);
    if (nolocal_lru_map) {
        uint32_t inner_key = 0;
        void* ret = bpf_map_lookup_elem(nolocal_lru_map, &inner_key);
        if (ret) {
            return bpf_ringbuf_output(ret, &inner_key, sizeof(inner_key), 0);
        } else {
            return 0;
        }
    }
    return 0;
}
