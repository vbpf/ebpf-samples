// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_ARRAY);
    // Declare keys and values using __type macro.
    __type(key, int);
    __uint(value, 0);
    __uint(max_entries, 1);
} map;

// This will be an unresolved symbol in the resulting .o file.
int ebpf_map_update_elem(struct bpf_map* map, const void* key,
                        const void* value, uint64_t flags);

struct ctx;

int func(struct ctx* ctx)
{
    // And we can furthermore pass some bad parameters in here.  These
    // would be illegal to pass to bpf_map_update_elem if it were resolved.
    return ebpf_map_update_elem(&map, (const void*)0, (const void*)0, 0);
}
