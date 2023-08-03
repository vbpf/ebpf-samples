# Copyright (c) Prevail Verifier contributors.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.10)
project(ebpf_samples)

include(FetchContent)

# libbpf is dual licensed under the GPL and the BSD license.  We use the BSD license.
FetchContent_Declare(
  libbpf
  GIT_REPOSITORY https://github.com/libbpf/libbpf.git
  GIT_TAG v1.2.0   
)

FetchContent_MakeAvailable(libbpf)

add_custom_target(samples ALL
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/badrelo.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/byteswap.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/ctxoffset.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/loop.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map_legacy.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_access.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_start_ok.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_overflow.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_reallocate.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/prog_array.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/ringbuf_uninit.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call_bad.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/twomaps.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/twostackvars.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/twotypes.o
                          ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o)

# We use custom commands here so that the same command will be used on
# Linux and Windows (where cmake would normally use cl instead of clang).

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/badhelpercall.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/badhelpercall.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/badhelpercall.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/badmapptr.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/badmapptr.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/badmapptr.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/badrelo.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/badrelo.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/badrelo.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/badrelo.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/byteswap.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/byteswap.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/byteswap.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/byteswap.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/ctxoffset.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/ctxoffset.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/ctxoffset.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/ctxoffset.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr2.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/exposeptr2.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/exposeptr2.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/loop.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/loop.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/loop.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/loop.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapoverflow.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapoverflow.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapoverflow.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapunderflow.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapunderflow.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapunderflow.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/mapvalue-overrun.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/mapvalue-overrun.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/mapvalue-overrun.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/map_in_map.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/map_in_map.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map_legacy.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/map_in_map_legacy.c
                   COMMAND clang -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/map_in_map_legacy.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/map_in_map_legacy.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/nullmapref.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/nullmapref.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/nullmapref.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/stackok.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/stackok.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/stackok.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_access.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_access.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_access.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_access.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_start_ok.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_start_ok.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_start_ok.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_start_ok.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_overflow.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_overflow.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_overflow.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_overflow.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_reallocate.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_reallocate.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/packet_reallocate.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/packet_reallocate.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/prog_array.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/prog_array.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/prog_array.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/prog_array.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/ringbuf_uninit.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/ringbuf_uninit.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/ringbuf_uninit.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/ringbuf_uninit.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/tail_call.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/tail_call.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call_bad.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/tail_call_bad.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/tail_call_bad.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/tail_call_bad.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/twomaps.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/twomaps.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/twomaps.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/twomaps.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/twostackvars.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/twostackvars.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c -g ${CMAKE_CURRENT_SOURCE_DIR}/src/twostackvars.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/twostackvars.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/twotypes.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/twotypes.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/twotypes.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/twotypes.o)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/wronghelper.c
                   COMMAND clang -g -target bpf -Wall -O2 -I ${libbpf_SOURCE_DIR}/src -c ${CMAKE_CURRENT_SOURCE_DIR}/src/wronghelper.c -o ${CMAKE_CURRENT_SOURCE_DIR}/build/wronghelper.o)
