       0:	r0 = get_prandom_u32:7()
       1:	r1 = r0
       2:	r1 &= 1
       3:	if r1 == 0 goto +3 <7>
       4:	r0 = le64 r0
       5:	exit
       6:	goto +25 <32>
       7:	r1 = r0
       8:	r1 &= 2
       9:	if r1 == 0 goto +3 <13>
      10:	r0 = le32 r0
      11:	exit
      12:	goto +19 <32>
      13:	r1 = r0
      14:	r1 &= 4
      15:	if r1 == 0 goto +3 <19>
      16:	r0 = le16 r0
      17:	exit
      18:	goto +13 <32>
      19:	r1 = r0
      20:	r1 &= 16
      21:	if r1 == 0 goto +3 <25>
      22:	r0 = be64 r0
      23:	exit
      24:	goto +7 <32>
      25:	r0 &= 32
      26:	if r0 == 0 goto +3 <30>
      27:	r0 = be32 r0
      28:	exit
      29:	goto +2 <32>
      30:	r0 = be16 r0
      31:	exit
      32:	r0 = 0
      33:	exit
