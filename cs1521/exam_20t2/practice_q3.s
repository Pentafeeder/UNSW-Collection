# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

# $t0: int value
# $t1: int bit_mask
# $t2: least_sig_byte
# $t3: second_least_sig_byte
main:
	li	$v0, 5
	syscall
	move	$t0, $v0

	li	$a0, 1

	li	$t1, 0xFF
	and	$t2, $t1, $t0
	sll	$t1, 8
	and	$t3, $t1, $t0
	srl	$t3, 8
	beq	$t3, $t2, is_equal

	li	$a0, 0
is_equal:
	li	$v0, 1
	syscall

	li	$a0, '\n'
	li	$v0, 11
	syscall

	li	$v0, 0
	jr	$ra
