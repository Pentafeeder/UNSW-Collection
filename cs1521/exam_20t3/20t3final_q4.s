# COMP1521 20T3 final exam Q4 starter code

# This code reads 1 integer and prints it

# Change it to read integers until low is greater or equal to high
# then print their difference

# $t0: int low
# $t1: int high 
# $t2: int x
# $t3: low - high
main:

while_loop_init:
	li 	$t0, 0
	li	$t1, 100

while_loop_cond:
	bge	$t0, $t1, while_loop_end
	
while_loop_body:
	li	$v0, 5		# scanf("%d", &x);
	syscall
	move 	$t2, $v0

	add 	$t0, $t0, $t2

	sub	$t1, $t1, $t2

	
while_loop_step:
	b	while_loop_cond

while_loop_end:
	sub	$t3, $t0, $t1

	move	$a0, $t3	# printf("%d\n", x);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall


	li	$v0, 0		# return 0
	jr	$ra
