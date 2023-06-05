// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

__attribute__((section("socket_filter"), used))
int reallocate_invalidates(struct __sk_buff* ctx)
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
