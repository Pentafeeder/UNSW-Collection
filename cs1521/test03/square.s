main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0

loop_i_lt_x__init:
	li	$t1, 0
loop_i_lt_x__cond:
	bge	$t1, $t0, loop_i_lt_x__end
loop_i_lt_x__body:
	loop_j_lt_x__init:
		li	$t2, 0
	loop_j_lt_x__cond:
		bge	$t2, $t0, loop_j_lt_x__end
	loop_j_lt_x__body:
		li	$a0, '*'	# printf("%c", '*');
		li	$v0, 11
		syscall	
	loop_j_lt_x__step:
		addi	$t2, $t2, 1
		b	loop_j_lt_x__cond
	
	loop_j_lt_x__end:

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall	
loop_i_lt_x__step: 
	addi	$t1, 1
	b	loop_i_lt_x__cond
loop_i_lt_x__end:
end:
	li	$v0, 0		# return 0
	jr	$ra
