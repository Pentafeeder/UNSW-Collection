#Program to print a string in assembly
#By Kevin Le z5481842

	.text
main:
	li 	$v0, 4
	la	$a0, string
	syscall

	li 	$v0, 0
	jr	$ra 

	.data
string:
	.asciiz "Well, this was a MIPStake!\n"