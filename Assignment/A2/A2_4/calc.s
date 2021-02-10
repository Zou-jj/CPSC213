.pos 0x100
                 ld $i, r0      # r0 = &i
                 ld (r0), r1    # r1 = i
                 ld $data, r2   # r2 = &data
                 ld (r2, r1, 4), r3 # r3 = data[i]
                 inc r1             # r1 ++
                 ld (r2, r1, 4), r4 # r4 = data[i]
                 add r3, r4         # r4 = r3 + r4
                 ld $y, r5          # r5 = &y
                 st r4, (r5)        # y = r4
                 ld $x, r6          # r6 = &x
                 ld $0xff ,r7       # r7 = 0xff
                 and r4, r7         # r7 = r7 && r4
                 st r7, (r6)
                 halt
.pos 0x1000
data:            .long 0x00000001
                 .long 0x00000001
                 .long 0x00000001
                 .long 0x00000001
.pos 0x2000
i:               .long 0x00000002
.pos 0x3000
x:               .long 0x00000002
.pos 0x4000
y:               .long 0x00000002