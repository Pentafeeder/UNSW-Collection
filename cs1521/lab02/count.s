# read a number n and print the integers 1..n one per line
#
# Before starting work on this task, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
#
# Kevin Le z5481482, 05/06/2023

#![tabsize(8)]

main:                 		# int main(void)
	# $t0: int number
	# $t1: int i
	la	$a0, prompt	# printf("Enter a number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", number);
	syscall
	move 	$t0, $v0

	li	$t1, 1

count_le_number__loop_condition:
	ble	$t1, $t0, count_le_number__loop_body

	b 	end

count_le_number__loop_body:
	move	$a0, $t1		# printf("%d", number);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

	addi 	$t1, $t1, 1
	b 	count_le_number__loop_condition

end:
	li	$v0, 0
	jr	$ra		# return 0

	.data
prompt:
	.asciiz "Enter a number: "
