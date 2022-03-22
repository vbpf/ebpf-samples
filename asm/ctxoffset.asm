; /home/alanjo/ebpf-verifier/ebpf-samples/src/ctxoffset.c:29
; int func(void* ctx)
       0:	r2 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/ctxoffset.c:31
;     uint32_t key = 1;
       1:	*(u32 *)(r10 - 4) = r2
; /home/alanjo/ebpf-verifier/ebpf-samples/src/ctxoffset.c:35
;     ctx = ((char*)ctx) + 8;
       2:	r1 += 8
       3:	r3 = r10
       4:	r3 += -4
; /home/alanjo/ebpf-verifier/ebpf-samples/src/ctxoffset.c:36
;     int result = bpf_sock_map_update(ctx, &map, &key, 0);
       5:	r2 = map_fd 1
       7:	r4 = 0
       8:	r0 = sock_map_update:53(ctx r1, map_fd r2, map_key r3, uint64_t r4)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/ctxoffset.c:37
;     return result;
       9:	exit
