// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __uint(max_entries, 1);
    __type(key, uint32_t);
    __type(value, uint32_t);
} map;

__attribute__((section("sockops"), used))
int func(void* ctx)
{
    uint32_t key = 1;

    // The following should fail because the sock_ops ctx isn't the same pointer passed in
    // but is offset 8 bytes into it.
    ctx = ((char*)ctx) + 8;
    int result = bpf_sock_map_update(ctx, &map, &key, 0);
    return result;
}
