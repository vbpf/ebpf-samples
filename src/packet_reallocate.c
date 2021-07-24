// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

struct sk_buff {
    uint32_t _[19];
    uint32_t data;
    uint32_t data_end;
};

struct ctx;

static int (*bpf_skb_change_head)(struct sk_buff *skb, uint32_t len, uint64_t flags) = (void*) 43;

__attribute__((section("socket_filter"), used))
int reallocate_invalidates(struct sk_buff* ctx)
{
    void *data_end = (void *)(long)ctx->data_end;
    void *data = (void *)(long)ctx->data;

    if (data + sizeof(int) > data_end)
        return 1;

    int value = *(int*)data;
    *(int*)data = value + 1;

    bpf_skb_change_head(ctx, 4, 0);

    value = *(int*)data;
    *(int*)data = value + 1;

    return 0;
}
