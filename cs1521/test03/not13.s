main:
	li	$v0, 5		# scanf("%d", &x);
	syscall			#
	move	$t0, $v0

	li	$v0, 5		# scanf("%d", &y);
	syscall			#
	move	$t1, $v0
loop__init:
	move	$t2, $t0
	addi	$t2, 1
loop__cond: 
	bge	$t2, $t1, loop__end	
loop__body: 

	beq	$t2, 13, loop__step	# if (i != 13)
	
	move	$a0, $t2		# printf("%d\n", i);
	li	$v0, 1
	syscall	

	li	$a0, '\n'	# printf("%c", '\n');
	li	$v0, 11
	syscall	
loop__step:
	addi	$t2, 1
	b	loop__cond

	
loop__end:

end:
	li	$v0, 0         # return 0
	jr	$ra
