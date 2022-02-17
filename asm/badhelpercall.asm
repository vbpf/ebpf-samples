; /home/alanjo/ebpf-verifier/ebpf-samples/src/badhelpercall.c:8
; int func()
       0:	r1 = r10
; /home/alanjo/ebpf-verifier/ebpf-samples/src/badhelpercall.c:14
;     return ebpf_get_current_comm(buffer, 20);
       1:	r1 += -1
       2:	r2 = 20
       3:	r0 = get_current_comm:16(out r1[r2], uint64_t r2)
       4:	exit
