# Copyright (c) Prevail Verifier contributors.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.10)
project(ebpf_samples)

add_custom_target(samples ALL
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o)

# We use custom commands here so that the same command will be used on
# Linux and Windows (where cmake would normally use cl instead of clang).

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/badhelpercall.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/badhelpercall.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/badmapptr.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/badmapptr.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr2.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr2.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapoverflow.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapoverflow.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapunderflow.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapunderflow.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapvalue-overrun.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapvalue-overrun.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/nullmapref.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/nullmapref.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/stackok.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/stackok.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/wronghelper.c
                   COMMAND clang -target bpf -Wall -O2 -c ${CMAKE_CURRENT_SOURCE_DIR}/src/wronghelper.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o)
