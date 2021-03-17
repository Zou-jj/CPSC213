ld  $a, r0
    ld  $0, r1
    ld  $0, r2

L0: ld  (r0, r1, 4), r4
    inc r1
    add r4, r2
    ld  $s, r4
    st r2, (r4)
    ld $i, r4
    st r1, (r4)
    ld  $-10, r3
    add r1, r3
    beq r3, L1
    br  L0

L1: halt

.pos 0x1000
a:  .long 1
    .long 2
    .long 3
    .long 4
    .long 5
    .long 7
    .long 8
    .long 9
    .long 10
    .long 11
    .long 324
i:  .long 0
s:  .long 0