; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapoverflow.c:29
; int func(struct ctx* ctx)
       0:	r1 = 10
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapoverflow.c:31
;     uint32_t key = 10;
       1:	*(u32 *)(r10 - 4) = r1
       2:	r1 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapoverflow.c:32
;     uint64_t value = 0;
       3:	*(u64 *)(r10 - 16) = r1
       4:	r2 = r10
       5:	r2 += -4
       6:	r3 = r10
       7:	r3 += -16
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapoverflow.c:36
;     return ebpf_map_update_elem(&map, &key, &value, 0);
       8:	r1 = map_fd 1
      10:	r4 = 0
      11:	r0 = map_update_elem:2(map_fd r1, map_key r2, map_value r3, uint64_t r4)
      12:	exit
