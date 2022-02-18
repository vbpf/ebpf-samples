; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:17
; int reallocate_invalidates(struct sk_buff* ctx)
       0:	r6 = 1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:19
;     void *data_end = (void *)(long)ctx->data_end;
       1:	r2 = *(u32 *)(r1 + 80)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:20
;     void *data = (void *)(long)ctx->data;
       2:	r7 = *(u32 *)(r1 + 76)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:22
;     if (data + sizeof(int) > data_end)
       3:	r3 = r7
       4:	r3 += 4
       5:	if r3 > r2 goto +10 <16>
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:25
;     int value = *(int*)data;
       6:	r2 = *(u32 *)(r7 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:26
;     *(int*)data = value + 1;
       7:	r2 += 1
       8:	*(u32 *)(r7 + 0) = r2
       9:	r6 = 0
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:28
;     bpf_skb_change_head(ctx, 4, 0);
      10:	r2 = 4
      11:	r3 = 0
      12:	r0 = skb_change_head:43(ctx r1, uint64_t r2, uint64_t r3)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:30
;     value = *(int*)data;
      13:	r1 = *(u32 *)(r7 + 0)
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:31
;     *(int*)data = value + 1;
      14:	r1 += 1
      15:	*(u32 *)(r7 + 0) = r1
; /home/alanjo/ebpf-verifier/ebpf-samples/src/packet_reallocate.c:34
; }
      16:	r0 = r6
      17:	exit
