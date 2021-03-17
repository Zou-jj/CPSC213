.pos 0x100
ld $s, r0 # current student address
ld (r0), r0
ld $0, r5 # index of current student
LOOP:
ld $0, r1 # r1 is sum value
ld $0, r2 # r2 is index
SUMGRADE:
mov r2, r3
deca r3
beq r3, ENDSUM
mov r0, r4 # get starting position of grade array
inca r4
ld (r4, r2, 4), r4 # gets the grade and sums it
add r4, r1
inc r2
br SUMGRADE
ENDSUM:

shr $2, r1 # r1 /= 4
st r1, 20(r0) # stores result into average

inc r5 # iterate through every student

ld $24, r1
add r1, r0

ld $n, r1
ld (r1), r1
not r1
inc r1
add r5, r1
beq r1, ENDLOOP
br LOOP

ENDLOOP:

# bubble sort
ld $s, r0
ld (r0), r0 # r0 = address of array base
ld $n, r1   
ld (r1), r1 # r1 = index of iterations starting from n going down

BUBBLE_SORT:

#
	ld $n, r2
	ld (r2), r2 # r2 = value of n
	dec r2		# r2 is index of student starting from n-1 counting down
	BUBBLE:
	#
		mov r2, r3
		shl $4, r3
		mov r2, r4
		shl $3, r4
		add r4, r3	# r3 = current student offset from array base
		add r0, r3	# r3 = current student address
		
		ld $-24, r4
		add r3, r4	# r4 = adjacent student address
		
		ld 20(r3), r6
		ld 20(r4), r7
		not r7
		inc r7
		add r6, r7 # r7 = currentgrade - adjacentgrade
		bgt r7, ENDSWAP
		
		ld $6, r5   # r5 = index of current slot of student to swap
		SWAP:
		dec r5
		ld (r3, r5, 4), r6
		ld (r4, r5, 4), r7
		st r6, (r4, r5, 4)
		st r7, (r3, r5, 4)
		bgt r5, SWAP
		ENDSWAP:
	#
	dec r2
	bgt r2, BUBBLE
#
dec r1		# r1--
bgt r1, BUBBLE_SORT
# end of sort

ld $n, r0 # r0 = address of n
ld (r0), r0 # r0 = n
shr $1, r0 # r0 = r0 / 2
ld $s, r1 # r1 = address of s
ld (r1), r1 # r1 = address of first student
ld $0, r4 # r4 = offset to median student

FINDMEDIAN:
beq r0, END
ld $6, r5 # r5 = 6
add r5, r4 # r4 = offset + 6
dec r0 # r0--
br FINDMEDIAN # goto FINDMEDIAN

END:
ld (r1, r4, 4), r6 # r6 = sid of median student
ld $m, r3 # r3 = address of m
st r6, (r3) # m = sid of median student
halt

.pos 0x1000
n:      .long 5       # just 3 student
m:      .long 0       # put the answer here
s:      .long base    # address of the array

.pos 0x2000
base:   .long 1234    # student ID
            .long 80      # grade 0
            .long 60      # grade 1
            .long 78      # grade 2
            .long 90      # grade 3
            .long 0       # computed average
s2:   		.long 1235    # student ID
            .long 20      # grade 0
            .long 60      # grade 1
            .long 78      # grade 2
            .long 90      # grade 3
            .long 0       # computed average
s3:		    .long 1236    # student ID
            .long 30      # grade 0
            .long 60      # grade 1
            .long 78      # grade 2
            .long 90      # grade 3
            .long 0       # computed average
s4:		    .long 1237    # student ID
            .long 1       # grade 0
            .long 2       # grade 1
            .long 3       # grade 2
            .long 4       # grade 3
            .long 0       # computed average
s5:		    .long 1238    # student ID
            .long 6       # grade 0
            .long 7       # grade 1
            .long 8       # grade 2
            .long 9       # grade 3
            .long 0       # computed average