# Copyright (c) Prevail Verifier contributors.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.10)
project(ebpf_samples)

add_custom_target(samples ALL
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o)

# We use a custom command here so that the same command will be used on
# Linux and Windows (where cmake would normally use cl instead of clang).
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c
                   COMMAND mkdir ${CMAKE_CURRENT_SOURCE_DIR}/build
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o)
