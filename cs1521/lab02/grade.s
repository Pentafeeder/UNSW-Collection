# read a mark and print the corresponding UNSW grade
#
# Before starting work on this task, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
#
# Kevin Le, z5481482, 05/06/2023

#![tabsize(8)]

main:
	# $t0: mark 
	la	$a0, prompt	# printf("Enter a mark: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", mark);
	syscall
	move 	$t0, $v0

	bge	$t0, 85, mark_ge_85

	bge	$t0, 75, mark_ge_75

	bge	$t0, 65, mark_ge_65

	bge	$t0, 50, mark_ge_50

	la	$a0, fl		# printf("FL\n");
	li	$v0, 4
	syscall
	b	epilogue
	


mark_ge_50:
	la	$a0, ps		# printf("PS\n");
	li	$v0, 4
	syscall
	b	epilogue

mark_ge_65:
	la	$a0, cr		# printf("CR\n");
	li	$v0, 4
	syscall
	b	epilogue

mark_ge_75:
	la	$a0, dn		# printf("DN\n");
	li	$v0, 4
	syscall
	b	epilogue

mark_ge_85:
	la	$a0, hd		# printf("HD\n");
	li	$v0, 4
	syscall
	b	epilogue

epilogue:
	li	$v0, 0
	jr	$ra		# return 0

	.data
prompt:
	.asciiz "Enter a mark: "
fl:
	.asciiz "FL\n"
ps:
	.asciiz "PS\n"
cr:
	.asciiz "CR\n"
dn:
	.asciiz "DN\n"
hd:
	.asciiz "HD\n"
