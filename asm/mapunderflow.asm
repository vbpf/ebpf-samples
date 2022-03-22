; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapunderflow.c:29
; int func(struct ctx* ctx)
       0:	r1 = -1 ll
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapunderflow.c:31
;     int key = -1;
       2:	*(u32 *)(r10 - 4) = r1
       3:	r1 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapunderflow.c:32
;     uint64_t value = 0;
       4:	*(u64 *)(r10 - 16) = r1
       5:	r2 = r10
       6:	r2 += -4
       7:	r3 = r10
       8:	r3 += -16
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapunderflow.c:37
;     return ebpf_map_update_elem(&map, &key, &value, 0);
       9:	r1 = map_fd 1
      11:	r4 = 0
      12:	r0 = map_update_elem:2(map_fd r1, map_key r2, map_value r3, uint64_t r4)
      13:	exit
