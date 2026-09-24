# COMP1521 22T3 ... final exam, question 5

# Modify the program below such that its output
# matches that of 22t3final_q4.

# $t0: uint32_t x
# $t1: int highest_consecutive
# $t2: uint32_t bit_mask
# $t3: int consecutive_set_bit
# $t4: uint32_t bit >> i
# $t5: int i

main:
	li	$v0, 5				# syscall 5: read_int
	syscall					#
	move	$t0, $v0			# scanf("%d, &x);

	# ADD YOUR CODE HERE

	li	$t1, 0
	li	$t2, 0x03
	andi	$t3, $t0, 1

	li	$t5, 0
for_loop_cond:
	bge	$t5, 32, for_loop_end
for_loop_body:
	and	$t4, $t0, $t2
	srlv	$t4, $t4, $t5

check_bit:

	

	beq	$t4, 0x03, increment_consecutive

	beq	$t4, 0x02, start_consecutive

	beq	$t4, 0x01, end_consecutive

end_consecutive:
	ble	$t3, $t1, reset_consecutive
	move	$t1, $t3

reset_consecutive:
	li	$t3, 0
	b	end_check_bit

increment_consecutive:
	addi	$t3, 1
	b	end_check_bit

start_consecutive:
	li	$t3, 1

end_check_bit:
	
	bge	$t5, 31, for_loop_step
	sll	$t2, $t2, 1

for_loop_step:
	addi	$t5, 1
	b	for_loop_cond

for_loop_end:

	ble	$t3, $t1, return_consecutive
	move	$t1, $t3

return_consecutive:

	li	$v0, 1				# syscall 1: print_int
	move	$a0, $t1			#
	syscall					# printf("%d", highest_consecutive);

	li	$v0, 11				# syscall 11: print_char
	li	$a0, '\n'			#
	syscall					# putchar('\n');

	li	$v0, 0				#
	jr	$ra				# return 0;
