// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

struct bpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
};

#define BPF_MAP_TYPE_ARRAY 2

__attribute__((section("maps"), used))
struct bpf_map map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(int),
     .value_size = 0,
     .max_entries = 1};

// This will be an unresolved symbol in the resulting .o file.
int bpf_map_update_elem(struct bpf_map* map, const void* key,
                        const void* value, uint64_t flags);

struct ctx;

int func(struct ctx* ctx)
{
    struct bpf_map map2;

    // And we can furthermore pass some bad parameters in here.  These
    // would be illegal to pass to bpf_map_update_elem if it were resolved.
    return bpf_map_update_elem(&map2, (const void*)0, (const void*)0, 0);
}
