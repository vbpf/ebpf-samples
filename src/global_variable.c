// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT

#include "bpf.h"

static volatile uint32_t global_var = 0;
static volatile uint32_t global_var_2 = 0;

int func(void* ctx) {
    global_var ++;
    global_var_2 += 2;
    return 0;
}
