
	.text


    # Locals:
    #	- $t0: int unix
    #	- $t1: int mips

main:



	li	$v0, 5		# syscall 5: read int
	syscall			#
	move 	$t0, $v0	# scanf("%d", &unix)

	li 	$v0, 5		# syscall 5: read int
	syscall			#
	move	$t1, $v0	# scanf("%d", &mips)


	li 	$v0, 0
	jr	$ra


	.data
