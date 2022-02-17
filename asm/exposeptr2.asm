; /home/alanjo/ebpf-verifier/ebpf-samples/src/exposeptr2.c:29
; int func(struct ctx* ctx)
       0:	*(u64 *)(r10 - 8) = r1
       1:	r1 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/exposeptr2.c:31
;     uint32_t value = 0;
       2:	*(u32 *)(r10 - 12) = r1
       3:	r2 = r10
       4:	r2 += -8
       5:	r3 = r10
       6:	r3 += -12
; /home/alanjo/ebpf-verifier/ebpf-samples/src/exposeptr2.c:35
;     return ebpf_map_update_elem(&map, &ctx, &value, 0);
       7:	r1 = map_fd 1
       9:	r4 = 0
      10:	r0 = map_update_elem:2(map_fd r1, map_key r2, map_value r3, uint64_t r4)
      11:	exit
