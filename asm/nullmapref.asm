; ./ebpf-samples/src/nullmapref.c:29
; test_repro
       0:	r6 = 1
; ./ebpf-samples/src/nullmapref.c:31
;     uint32_t key = 1;
       1:	*(u32 *)(r10 - 4) = r6
       2:	r2 = r10
       3:	r2 += -4
; ./ebpf-samples/src/nullmapref.c:33
;     uint32_t* value = ebpf_map_lookup_elem(&test_map, &key);
       4:	r1 = map_fd 1
       6:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       7:	*(u32 *)(r0 + 0) = r6
; ./ebpf-samples/src/nullmapref.c:37
;     *value = 1;
       8:	r0 = 0
; ./ebpf-samples/src/nullmapref.c:39
;     return 0;
       9:	exit
