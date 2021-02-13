.pos 0x1000
code:

    # v0 = s.x[i]
    ld $s, r0           # r0 = address of s
    ld $i, r1           # r1 = address of i
    ld 0(r1), r1        # r1 = i
    ld (r0, r1, 4), r2  # r2 = s.x[i]
    ld $v0, r3          # r3 = address of v0
    st r2, 0(r3)        # v0 = s.x[i]

    # v1 = s.y[i]
    ld $s, r0           # r0 = address of s
    ld 8(r0), r0        # r0 = s.y
    ld $i, r1           # r1 = address of i
    ld 0(r1), r1        # r1 = i
    ld (r0, r1, 4), r2  # r2 = s.y[i]
    ld $v1, r3          # r3 = address of v1
    st r2, 0(r3)        # v1 = s.y[i]

    # v2 = s.z->x[i]
    ld $s, r0           # r0 = address of s
    ld 12(r0), r0       # r0 = s.z
    ld $i, r1           # r1 = address of i
    ld 0(r1), r1        # r1 = i
    ld (r0, r1, 4), r2  # r2 = s.x[i]
    ld $v2, r3          # r3 = address of v2
    st r2, 0(r3)        # v2 = s.x[i]

    # v3 = s.z->z->y[i]
    ld $s, r0           # r0 = address of s
    ld 12(r0), r0       # r0 = s.z
    ld 12(r0), r0       # r0 = s.z->z
    ld 8(r0), r0        # r0 = s.z->z->y
    ld $i, r1           # r1 = address of i
    ld 0(r1), r1        # r1 = i
    ld (r0, r1, 4), r2  # r2 = s.z->z->y[i]
    ld $v3, r3          # r3 = address of v3
    st r2, 0(r3)        # v3 = s.z->z->y[i]

    halt 

.pos 0x2000
static:
i:      .long 1
v0:     .long 0
v1:     .long 0
v2:     .long 0
v3:     .long 0
s:      .long 2         # s.x[0]
        .long 3         # s.x[1]
        .long s_y       # s.y
        .long s_z       # s.z

.pos 0x3000
heap:
s_y:    .long 1         # s.y[0]
        .long 2         # s.y[1]
s_z:    .long 4         # s.z -> x[0]
        .long 5         # s.z -> x[1]
        .long 0         # s.z -> y
        .long s_z_z     # s.z -> z
s_z_z:  .long 2         # s.z -> z -> x[0]
        .long 3         # s.z -> z -> x[1]
        .long s_z_z_y   # s.z -> z -> y
        .long 0         # s.z -> z -> z
s_z_z_y:.long 7         # s.z -> z -> y[0]
        .long 8         # s.z -> z -> y[1]
