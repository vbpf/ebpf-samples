// Copyright (c) Microsoft Corporation
// SPDX-License-Identifier: MIT

#include "bpf.h"

__attribute__((section("xdp"), used)) void
dependent_read(struct xdp_md* ctx)
{
    // Load data into r7
    asm volatile("r7 = %0" : : "r"(ctx->data));
    // Load data_end into r8
    asm volatile("r8 = %0" : : "r"(ctx->data_end));
    // Compute packet length and store in r8.
    asm volatile("r8 -= r7");
    // Set flag register to 0
    asm volatile("r9 = 0x0");
    // Check if packet length (r8) is less than 4
    asm volatile("if r8 < 4 goto l1");
    // Set flag register to 1 (only hit if r8 >= 4).
    asm volatile("r9 = 0x1");
    // If flag is not set (and hence r8 < 4), exit
    asm volatile("l1: if r9 == 0x0 goto l2");
    // Access first 4 bytes of packet
    asm volatile("r6 = *(u32 *)(r7 + 0x0)");
    // Exit
    asm volatile("l2: r0 = 0");
}
