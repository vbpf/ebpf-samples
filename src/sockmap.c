// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_SOCKMAP);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 64);
} sockmap;

__attribute__((section(".maps"), used))
struct {
    __uint(type, BPF_MAP_TYPE_SOCKHASH);
    __type(key, uint32_t);
    __type(value, uint32_t);
    __uint(max_entries, 64);
} sockhash;

__attribute__((section("sk_skb/stream_verdict"), used))
int test_sockmap(struct __sk_buff* skb)
{
    uint32_t key = 0;
    return bpf_sk_redirect_map(skb, &sockmap, key, 0);
}
