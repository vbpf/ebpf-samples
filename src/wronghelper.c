// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct
{
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 1);
} map;

__attribute__((section("xdp"), used))
int func(void* ctx)
{
    uint32_t key = 1;

    // The following should fail because the ctx doesn't match, and in particular
    // the memory pointed to by ctx might be smaller than the memory read by the helper.
    int result = bpf_sock_map_update(ctx, &map, &key, 0);
    return result;
}
