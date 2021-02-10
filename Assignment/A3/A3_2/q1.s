.pos 0x100

    # i = a[3]
    ld $a, r0           # r0 = address of a
    ld $i, r1           # r1 = address of i
    ld 12(r0), r2       # r2 = a[3]
    st r2, 0(r1)        # i = a[3]

    # i = a[i]
    ld $a, r0           # r0 = address of a
    ld $i, r1           # r1 = address of i
    ld (r1), r2         # r2 = i
    ld (r0, r2, 4), r3  # r3 = a[i]
    st r3, 0(r1)        # i = a[i]

    # p = &j
    ld $j, r0           # r0 = address of j
    ld $p, r1           # r1 = address of p
    st r0, 0(r1)        # p = &j

    # *p = 4
    ld $p, r0           # r0 = address of p
    ld 0(r0), r0        # r0 = p = &j
    ld $4, r1           # r1 = 4
    st r1, 0(r0)        # *p = 4

    # p = &a[a[2]]
    ld $p, r0           # r0 = address of p
    ld $a, r1           # r1 = address of a
    ld 8(r1), r2        # r2 = a[2]
    add r2, r1          # r1 = r1 + a[2]
    add r2, r1          # r1 = r1 + a[2]
    add r2, r1          # r1 = r1 + a[2]
    add r2, r1          # r1 = r1 + a[2]
    st r1, 0(r0)        # p = r1 = address of a + 4 * a[2]

    # *p = *p + a[4]
    ld $p, r0           # r0 = address of p
    ld 0(r0), r0        # r0 = p
    ld 0(r0), r1        # r1 = *p
    ld $a, r2           # r2 = address of a
    ld 16(r2), r2       # r2 = a[4]
    add r2, r1          # r1 = r1 + r2 = *p + a[4]
    st r1, 0(r0)        # *p = r1

    halt

.pos 0x200
# Data area

i:  .long 0             # a
j:  .long 0             # b
p:  .long 0             # p
a:  .long 0             # a[0]
    .long 0             # a[1]
    .long 3             # a[2]
    .long 8             # a[3]
    .long 8             # a[4]
    .long 0             # a[5]
    .long 0             # a[6]
    .long 0             # a[7]
    .long 0             # a[8]
    .long 0             # a[9]
