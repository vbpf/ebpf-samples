// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
typedef unsigned char uint8_t;

struct test_md
{
    uint8_t* data_start;
    uint8_t* data_end;
};

#define ARRAY_LENGTH 40

__attribute__((section("test_md"), used)) int
foo(struct test_md* ctx)
{
    int index;
    int cumul = 0;
    uint8_t array[ARRAY_LENGTH] = {0};

    for (index = 0; index < sizeof(array); index++) {
        if ((ctx->data_start + index) >= ctx->data_end)
            break;

        array[index] = 1;
    }

    for (index = 0; index < sizeof(array); index++) {
        cumul += array[index];
    }
    return cumul;
}
