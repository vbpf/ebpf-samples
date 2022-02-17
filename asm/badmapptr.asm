; /home/alanjo/ebpf-verifier/ebpf-samples/src/badmapptr.c:29
; test_repro(void* ctx)
       0:	r6 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/badmapptr.c:31
;     uint32_t key = 1;
       1:	*(u32 *)(r10 - 4) = r6
; /home/alanjo/ebpf-verifier/ebpf-samples/src/badmapptr.c:37
;     uint32_t* value = ebpf_map_lookup_elem(map + 1, &key);
       2:	r1 = map_fd 1
       4:	r1 += 28
       5:	r2 = r10
       6:	r2 += -4
       7:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       8:	if r0 != 0 goto +1 <10>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/badmapptr.c:39
;     return (value != 0);
       9:	r6 = 0
      10:	r0 = r6
      11:	exit

