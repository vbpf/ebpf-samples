; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:35
; int func(void* ctx) {
       0:	r6 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:36
;     uint32_t outer_key = 0;
       1:	*(u32 *)(r10 - 4) = r6
       2:	r2 = r10
       3:	r2 += -4
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:37
;     void* nolocal_lru_map = bpf_map_lookup_elem(&array_of_maps, &outer_key);
       4:	r1 = map_fd 1
       6:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:38
;     if (nolocal_lru_map) {
       7:	if r0 == 0 goto +11 <19>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:39
;         uint32_t inner_key = 0;
       8:	*(u32 *)(r10 - 8) = r6
       9:	r2 = r10
      10:	r2 += -8
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:40
;         void* ret = bpf_map_lookup_elem(nolocal_lru_map, &inner_key);
      11:	r1 = r0
      12:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:41
;         if (ret) {
      13:	if r0 != 0 goto +5 <19>
      14:	r2 = r10
      15:	r2 += -8
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:44
;             ret = bpf_map_lookup_elem(&inner_map, &inner_key);
      16:	r1 = map_fd 2
      18:	r0 = map_lookup_elem:1(map_fd r1, map_key r2)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/map_in_map.c:49
; }
      19:	r0 = 0
      20:	exit
