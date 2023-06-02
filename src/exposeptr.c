// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    __type(key, int);
    __type(value, uint64_t);
    __uint(max_entries, 1);
} map;

struct ctx;

int func(struct ctx* ctx)
{
    uint32_t key = 0;

    // The following should fail verification since it stores
    // a pointer in shared memory, thus exposing it to user-mode apps.
    return bpf_map_update_elem(&map, &key, &ctx, 0);
}
