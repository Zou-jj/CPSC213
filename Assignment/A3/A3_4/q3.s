.pos 0x100

    # a = 3
    ld $a, r0           # r0 = address of a
    ld $3, r1           # r1 = 3
    st r1, 0(r0)        # tmp = 3

    # p = &a
    ld $a, r0           # r0 = address of a
    ld $p, r1           # r1 = address of p
    st r0, 0(r1)        # p = &a

    # *p = *p - 1
    ld $p, r0           # r0 = address of p
    ld 0(r0), r0        # r0 = p
    ld 0(r0), r1        # r1 = *p
    dec r1              # r1 = *p - 1
    st r1, 0(r0)        # *p = *p - 1

    # p = &b[0]
    ld $b, r0           # r0 = address of b
    ld $p, r1           # r1 = address of p
    st r0, 0(r1)        # p = &b[0]

    # p++
    ld $p, r0           # r0 = address of p
    ld 0(r0), r1        # r1 = p
    inca r1             # r1 = p + 1
    st r1, 0(r0)        # p = p + 1

    # p[a] = b[a]
    ld $p, r0           # r0 = address of p
    ld 0(r0), r0        # r0 = p
    ld $b, r1           # r1 = address of b
    ld $a, r2           # r2 = address of a
    ld 0(r2), r2        # r2 = a
    ld (r1, r2, 4), r3  # r3 = b[a]
    st r3, (r0, r2, 4)  # p[a] = b[a]

    # *(p+3) = b[0]
    ld $p, r0           # r0 = address of p
    ld 0(r0), r0        # r0 = p
    ld $b, r1           # r1 = address of b
    ld 0(r1), r2        # r2 = b[0]
    st r2, 12(r0)       # *(p+3) = b[0]

    halt 

.pos 0x200
# Data area

a:  .long 0             # a
p:  .long 0             # p
b:  .long 1             # b[0]
    .long 2             # b[1]
    .long 3             # b[2]
    .long 4             # b[3]
    .long 5             # b[4]
