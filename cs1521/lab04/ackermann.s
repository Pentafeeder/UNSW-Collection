########################################################################
# .DATA
# Here are some handy strings for use in your code.
	.data
prompt_m_str:	.asciiz	"Enter m: "
prompt_n_str:	.asciiz	"Enter n: "
result_str_1:	.asciiz	"Ackermann("
result_str_2:	.asciiz	", "
result_str_3:	.asciiz	") = "

########################################################################
# .TEXT <main>
	.text
main:

	# Args: void
	# Returns: int
	#
	# Frame:	[$ra, $s0, $s1]
	# Uses: 	[$ra, $s0, $s1, $t0, $a0, $v0]
	# Clobbers:	[$t0, $v0, $a0]
	#
	# Locals:
	#   - $s0: int m
	#   - $s1: int n
	#   - $t0: int f
	#
	# Structure:
	#   - main
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

main__prologue:

	# TODO: set up your stack frame
	begin
	push	$ra
	push	$s0
	push	$s1
main__body:

	# TODO: add your function body here
	li	$v0, 4			# syscall 4: print str
	la	$a0, prompt_m_str
	syscall				# printf(Enter m: )

	li	$v0, 5
	syscall
	move	$s0, $v0

	li	$v0, 4			# syscall 4: print str
	la	$a0, prompt_n_str
	syscall				# printf(Enter m: )

	li	$v0, 5
	syscall
	move	$s1, $v0

	move	$a0, $s0
	move 	$a1, $s1

	jal	ackermann
	move	$t0, $v0

	li	$v0, 4			# syscall 4: print str
	la	$a0, result_str_1
	syscall				# printf("Ackermann(")

	li	$v0, 1			# syscall 1: print int
	move	$a0, $s0
	syscall				# printf("%d", m)

	li	$v0, 4			# syscall 4: print str
	la	$a0, result_str_2
	syscall				# printf(", ")

	li	$v0, 1			# syscall 1: print int
	move	$a0, $s1
	syscall				# printf("%d", n)

	li	$v0, 4			# syscall 4: print str
	la	$a0, result_str_3
	syscall				# printf(") = ")

	li	$v0, 1
	move	$a0, $t0
	syscall				# printf("%d", f)

	li	$v0, 11			# syscall 11: print char 
	la	$a0, '\n'
	syscall				# putchar('\n')
main__epilogue:

	# TODO: clean up your stack frame
	pop	$s1
	pop	$s0
	pop	$ra
	
	li	$v0, 0
	end


	jr	$ra			# return 0;

########################################################################
# .TEXT <ackermann>
	.text
ackermann:

	# Args:
	#   - $a0: int m
	#   - $a1: int n
	# Returns: int
	#
	# Frame:	[$ra, $s0, $s1]
	# Uses: 	[$ra, $s0, $s1, $t0, $a0, $a1, $v0]
	# Clobbers:	[$v0, $a0, $a1, $t0]
	#
	# Locals:
	#   - $s0: int m
	#   - $s1: int n
	#
	# Structure:
	#   - ackermann
	#     -> [prologue]
	#     -> [body]
	#	  -> [m_eq_0]
	#	  -> [n_eq_0]
	#	  -> [neither_m_n_0]
	#     -> [epilogue]

ackermann__prologue:

	# TODO: set up your stack frame
	begin
	push	$ra
	push	$s0
	push 	$s1
	
ackermann__body:
	move 	$s0, $a0
	move 	$s1, $a1
	# TODO: add your function body here
	
	beqz	$s0, m_eq_0
	beqz	$s1, n_eq_0
	b	neither_m_n_0
	m_eq_0:
		addi	$s1, 1
		
		move	$v0, $s1 
		b	ackermann__epilogue

	n_eq_0:
		move	$a0, $s0
		sub	$a0, $a0, 1		
		li	$a1, 1
		jal	ackermann
		b	ackermann__epilogue
	neither_m_n_0:
	move 	$a0, $s0	# ackermnann(m, n - 1)
	move	$a1, $s1
	sub	$a1, $a1, 1
	jal	ackermann
	move	$t0, $v0

	move 	$a0, $s0	# ackermann(m - 1, ackermann(m, n - 1))
	sub	$a0, $a0, 1
	move	$a1, $t0
	jal	ackermann


ackermann__epilogue:

	# TODO: clean up your stack frame
	pop	$s1
	pop	$s0
	pop	$ra
	end
	jr	$ra
