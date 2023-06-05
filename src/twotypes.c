// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, int);
    __uint(value, 1024);
    __uint(max_entries, 1);
} map;

struct ctx;

int func(struct ctx* ctx)
{
    uint32_t rand32 = bpf_get_prandom_u32();
    uint8_t stack_buffer[256] = { 0 };
    *(uint32_t*)stack_buffer = rand32;

    int map_key = 0;
    uint8_t* map_value = (uint8_t*)bpf_map_lookup_elem(&map, &map_key);
    if (map_value == 0)
        return 0;

    uint8_t* ptr;
    if (rand32 & 1) {
        ptr = map_value;
    } else {
        ptr = stack_buffer + 128;
    }

    return (*ptr == stack_buffer[0]) ? 1 : 0;
}
