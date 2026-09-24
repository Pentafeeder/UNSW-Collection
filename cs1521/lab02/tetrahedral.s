# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number
#
# Before starting work on this task, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
#
# Kevin Le (z5481482), 13/06/2023

#![tabsize(8)]

#	$t0: int how_many
#	$t1: int total
#	$t2: int n
#	$t3: int j
#	$t4: int i

main:				# int main(void) {

	la	$a0, prompt	# printf("Enter how many: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", how_many);
	syscall
	move	$t0, $v0	# store input into $t0 (how_many)

	li 	$t2, 1 		# n = 1

	bgt	$t2, $t0, end 	# if (n > how_many) goto end
n_le_how_many:
	li	$t1, 0
	li	$t3, 1

	bgt	$t3, $t2, exit_j_le_n

j_le_n:
	li	$t4, 1

	bgt 	$t4, $t3, exit_i_le_j 	# pre-condition

i_le_j:
	add	$t1, $t1, $t4
	addi 	$t4, $t4, 1

	ble  	$t4,$t3, i_le_j	

exit_i_le_j:
	addi	$t3, $t3, 1

	ble	$t3, $t2, j_le_n

exit_j_le_n:
	li	$v0, 1
	move	$a0, $t1	# printf("%d", total);
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

	addi 	$t2, $t2, 1

	ble	$t2, $t0, n_le_how_many

end:
	li	$v0, 0
	jr	$ra		# return 0

	.data
prompt:
	.asciiz "Enter how many: "
