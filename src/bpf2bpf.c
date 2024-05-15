// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

int plus1(int x) {
    return x + 1;
}

__attribute__((optnone))
int func(void* ctx) {
    return plus1(3);
}
