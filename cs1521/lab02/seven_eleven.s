# Read a number and print positive multiples of 7 or 11 < n
#
# Before starting work on this task, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
#
# Kevin Le z5481482, 05/06/2023

#![tabsize(8)]
# optimise later
main:				# int main(void) {
	# $t0: int number
	# $t1: int i
	# $t2: i % 7
	# $t3: i % 11

	la	$a0, prompt	# printf("Enter a number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", number);
	syscall
	move 	$t0, $v0

i_init_loop:
	li	$t1, 1

i_ge_number__condition_loop:
	bge 	$t1, $t0, end

i_ge_number__body_loop:
	rem 	$t2, $t1, 7
	beqz	$t2, i_div_7_or_11_eq_0__condition

	rem 	$t3, $t1, 11
	beqz	$t3, i_div_7_or_11_eq_0__condition
	
	addi 	$t1, $t1, 1

	b 	i_ge_number__condition_loop

i_div_7_or_11_eq_0__condition:

	move	$a0, $t1		# printf("%d", i);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

	addi 	$t1, $t1, 1

	b 	i_ge_number__condition_loop

end:
	li	$v0, 0
	jr	$ra		# return 0

	.data
prompt:
	.asciiz "Enter a number: "
