// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#define BPF_MAP_TYPE_HASH 1
#define BPF_MAP_TYPE_ARRAY 2
#define BPF_MAP_TYPE_PROG_ARRAY 3
#define BPF_MAP_TYPE_ARRAY_OF_MAPS 12
#define BPF_MAP_TYPE_RINGBUF 27

#define __uint(name, val) int (*name)[val]
#define __type(name, val) typeof(val) *name
#define __array(name, val) typeof(val) *name[]

struct xdp_md {
    uint32_t data;
    uint32_t data_end;
    uint32_t data_meta;
    uint32_t _1;
    uint32_t _2;
    uint32_t _3;
};

struct sk_buff {
    uint32_t _[19];
    uint32_t data;
    uint32_t data_end;
};

struct bpf_map;
struct bpf_sock_ops;

static void* (*bpf_map_lookup_elem)(struct bpf_map* map, const void* key) = (void*) 1;
static int (*bpf_map_update_elem)(struct bpf_map* map, const void* key,
                                   const void* value, uint64_t flags) = (void*) 2;
static int (*get_prandom_u32)() = (void*)7;
static long (*bpf_tail_call)(void *ctx, struct bpf_map *prog_array_map, uint32_t index) = (void*) 12;
static int (*bpf_get_current_comm)(char* buffer, uint32_t buffer_size) = (void*) 16;
static int (*bpf_skb_change_head)(struct sk_buff *skb, uint32_t len, uint64_t flags) = (void*) 43;
static int (*bpf_sock_map_update)(struct bpf_sock_ops *skops, struct bpf_map *map, void *key, uint64_t flags) = (void*) 53;
static long (*bpf_ringbuf_output)(void *ringbuf, void *data, uint64_t size, uint64_t flags) = (void *) 130;

