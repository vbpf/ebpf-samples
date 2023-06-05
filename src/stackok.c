// Copyright (c) Prevail Verifier contributors.
// SPDX-License-Identifier: MIT
#include "bpf.h"

int func(void* ctx)
{
   // Initialize an array of 256 bytes (to all zeroes in this example).
   char array[256] = "";

   // Set index to a random value in the interval [0,255].
   uint32_t rand32 = bpf_get_prandom_u32();
   uint32_t index = *(unsigned char*)&rand32;

   // Return the array element at the specified index.
   return array[index];
}
