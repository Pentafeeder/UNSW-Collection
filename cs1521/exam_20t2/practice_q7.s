# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

# $t0: int i
# $t1: int sum
# $t2: int x
# $t3: temp value

main:

	li	$t0, 0
	li	$t1, 0

while_lt_42_cond:
	bge	$t1, 42, while_lt_42_end
while_lt_42_body:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t2, $v0

	mul	$t3, $t0, 4
	sw	$t2, numbers($t3) #numbers[i] = x

	addi	$t0, 1		# i++
	add	$t1, $t1, $t2	# sum += x

while_lt_42_step:
	b	while_lt_42_cond

while_lt_42_end:


while_i_gt_0_cond:
	ble	$t0, 0, while_i_gt_0_end

while_i_gt_0_body:
	addi	$t0, -1

	mul	$t3, $t0, 4
	lw	$t3, numbers($t3)

	move	$a0, $t3	# printf("%d\n", numbers[i]);
	li	$v0, 1
	syscall

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall

while_i_gt_0_step:
	b	while_i_gt_0_cond
while_i_gt_0_end:
	
	

	li	$v0, 0		# return 0
	jr	$ra


	.data
numbers:
	.space 	4 * 1000