; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:26
; int func(void* ctx)
       0:	r1 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:28
;     uint32_t key = 1;
       1:	*(u32 *)(r10 - 4) = r1
       2:	r2 = r10
       3:	r2 += -4
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:30
;     uint64_t* ptr = bpf_map_lookup_elem(&map, &key);
       4:	r1 = map_fd 1
       6:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
       7:	r1 = r0
       8:	r0 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:31
;     if (ptr == 0) {
       9:	if r1 == 0 goto +1 <11>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:37
;     uint64_t i = *ptr;
      10:	r0 = *(u64 *)(r1 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/mapvalue-overrun.c:39
; }
      11:	exit
