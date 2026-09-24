# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

# $t0: int sum
# $t1: int x
main:

	li	$t0, 0

while_loop_cond:
	bge	$t0, 42, while_loop_end

while_loop_body:
	li	$v0, 5		# scanf("%d", &x);
	syscall	
	move	$t1, $v0

	add	$t0, $t0, $t1

while_loop_step:
	b	while_loop_cond
while_loop_end:
	
	move	$a0, $t0	# printf("%d", sum);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

	li	$v0, 0		# return 0
	jr	$ra
