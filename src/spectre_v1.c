// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

struct ctx;

#define BPF_MAP_TYPE_ARRAY 2

struct ebpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
};

__attribute__((section("maps"), used))
struct ebpf_map map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(int),
     .value_size = sizeof(uint64_t) * 8 * 32,
     .max_entries = 1};


static void* (*bpf_map_lookup_elem)(struct ebpf_map* map, const void* key) = (void*) 1;

__attribute__((section("1"), used))
int spectre_v1_1(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index = shared[0];
    int res = 1;
    if (index < 8 * 4) {
        int secret = shared[index];
        if (secret & 1) {
            res = shared[8*2];
        } else {
            res = shared[8*3];
        }
    }
    return res;
}


__attribute__((section("2"), used))
int spectre_v1_2(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index = shared[0];
    int res = 1;
    if (index < 8 * 4) {
        res = shared[(shared[index]&1) * 8];
    }
    return res;
}


__attribute__((section("3"), used))
int spectre_v1_3(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index = shared[0];
    int res = 1;
    if (index < 8 * 4) {
        res = shared[(shared[2 * index]&1) * 8];
    }
    return res;
}

/// Check bounds with & - not supported by the verifier currently
__attribute__((section("4"), used))
int spectre_v1_4(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index = shared[0];
    int res = 1;
    if ((index & 0xFFF) == index) {
        int secret = shared[index];
        if (secret & 1) {
            res = shared[8*2];
        } else {
            res = shared[8*3];
        }
    }
    return res;
}

__attribute__((section("5"), used))
int spectre_v1_5(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index = shared[0];
    uint64_t k = shared[1];
    int res = 1;
    if (index < 8 * 4) {
        if (shared[index] == k)
            res = shared[23];
    }
    return res;
}

__attribute__((section("6"), used))
int spectre_v1_6(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t* shared = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    if (shared == 0)
        return 0;
    uint64_t index1 = shared[0];
    uint64_t index2 = shared[1];
    int res = 1;
    if (index1 + index2 < 8 * 4) {
        int secret = shared[index1 + index2];
        if (secret & 1) {
            res = shared[8*2];
        } else {
            res = shared[8*3];
        }
    }
    return res;
}

__attribute__((section("type_confusion"), used))
int spectre_v1_type_confusion(struct ctx* ctx)
{
    uint32_t key = 0;
    uint64_t index_of_secret;
    {
        uint64_t* ptr_1 = (uint64_t*)bpf_map_lookup_elem(&map, &key);
        if (ptr_1 == 0)
            return 0;
        index_of_secret = ptr_1[0];
    }
    uint64_t* ptr = (uint64_t*)bpf_map_lookup_elem(&map, &key);
    uint32_t* stack_ptr = &key;
    // %0 = ptr to a map array entry (verified != NULL)
    // %1 = scalar value controlled by attacker
    // %2 = ptr to stack slot (verified != NULL)
    asm volatile("%3 = *(u64 *)(%0 + 0)\n"
                 "if %3 != 0x0 goto +1\n"
                 "%2 = %1\n"
                 "if %3 != 0x1 goto +5\n"
                 "%1 = *(u8 *)(%2 + 0)\n"
                 "%1 &= 1\n"
                 "%1 *= 8\n"
                 "%0 += %1\n"
                 "%0 = *(u64 *)(%0 + 0)\n"
                 :
                 : "r" (ptr), "r" (index_of_secret), "r" (stack_ptr), "r" (key)
                 );
    return (long long)ptr;
}