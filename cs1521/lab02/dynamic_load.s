# Written by Kevin Le (z5481482), 13/06/2023

main: 
	li	$v0, 0
	jr	$ra		# return 0

prompt:
	.asciiz	"Enter mips instruction as integers, -1 to finish:\n"