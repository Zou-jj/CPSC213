.pos 0x100

    # a = 3
    ld $a, r0           # r0 = address of a
    ld 0(r0), r0        # r0 = a = &A
    ld 16(r0), r0       # r0 = z
    ld 16(r0), r0       # r0 = j.z = &B
    ld 12(r0), r0       # r0 = j.y[2]
    ld $b, r1           # r1 = address of b
    st r0, 20(r1)       # b.k = rhs

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
