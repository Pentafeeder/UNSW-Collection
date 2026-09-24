# Read three numbers `start`, `stop`, `step`
# Print the integers bwtween `start` and `stop` moving in increments of size `step`
#
# Before starting work on this task, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
#
# YOUR-NAME-HERE, DD/MM/YYYY

#![tabsize(8)]

main:				# int main(void)
	# $t0: int start
	# $t1: int stop
	# $t2: int step
	# $t3: int i

	la	$a0, prompt1	# printf("Enter the starting number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", start);
	syscall
	move 	$t0, $v0

	la	$a0, prompt2	# printf("Enter the stopping number: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", stop);
	syscall
	move 	$t1, $v0

	la	$a0, prompt3	# printf("Enter the step size: ");
	li	$v0, 4
	syscall

	li	$v0, 5		# scanf("%d", step);
	syscall
	move 	$t2, $v0

loop_init1:
	move 	$t3, $t0

condition1:
	bge	$t1, $t0, condition2

nested_condition1:
	bgez	$t2, condition2 

loop_condition1:
	blt	$t3, $t1, loop_init2
	b 	loop_body

loop_init2:
	move 	$t3, $t0

condition2:
	ble	$t1, $t0, end

nested_condition2:
	blez 	$t2, end

loop_condition2:
	bgt 	$t3, $t1, end
	b 	loop_body


loop_body:
	move	$a0, $t3	# printf("%d", i);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

	add 	$t3, $t3, $t2

	bge 	$t3, $t1, condition1
	ble	$t3, $t1, condition2

end:
	li	$v0, 0
	jr	$ra		# return 0

	.data
prompt1:
	.asciiz "Enter the starting number: "
prompt2:
	.asciiz "Enter the stopping number: "
prompt3:
	.asciiz "Enter the step size: "
