# Kevin Le (z5481482), 19/06/2023

########################################################################
# .DATA
# Here are some handy strings for use in your code.

	.data
prompt_str:
	.asciiz "Enter a random seed: "
result_str:
	.asciiz "The random result is: "

########################################################################
# .TEXT <main>
	.text
main:

	# Args: void
	# Returns: int
	#
	# Frame:	[$s0, $ra]
	# Uses: 	[$ra, $s0, $t0, $v0, $a0]
	# Clobbers:	[$t0, $v0, $a0]
	#
	# Locals:
	#   - $t0: int random_seed
	#   - $s0: int value
	#
	# Structure:
	#   - main
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

main__prologue:
	begin

	# TODO: add code to set up your stack frame here 
	push	$ra
main__body:
	# TODO: complete your function body here
	li 	$v0, 4		# syscall 4: print string
	la	$a0, prompt_str	
	syscall			# printf("Enter a random seed: ")

	li	$v0, 5		# syscall 5: read int
	syscall
	move	$a0, $v0	# scanf("%d", &random_seed)

	jal 	seed_rand
	

	li	$a0, 100
	jal	rand
	move	$a0, $v0	# value = rand(value)

	jal	add_rand
	move	$a0, $v0	# value = add_rand(value)

	jal	sub_rand
	move	$a0, $v0	# value = sub_rand(value)

	jal	seq_rand
	move	$t0, $v0	# value = seq_rand(value)

	li	$v0, 4		# syscall 4: print string
	la	$a0, result_str
	syscall			# printf("The random result is: ")

	
	li	$v0, 1		# syscall 1: print int
	move	$a0, $t0
	syscall			# printf("%d", value)

	li	$v0, 11		# syscall 11: print char
	li	$a0, '\n'
	syscall			#printf("\n")

main__epilogue:
	# TODO: add code to clean up stack frame here
	pop	$ra
	end

	li	$v0, 0
	jr	$ra				# return 0;

########################################################################
# .TEXT <add_rand>
	.text
add_rand:
	# Args:
	#   - $a0: int value
	# Returns: int
	#
	# Frame:	[$s0, $ra]
	# Uses: 	[$ra, $s0, $v0, $a0]
	# Clobbers:	[$a0, $v0]
	#
	# Locals: 
	#	- $s0: int value
	#
	# Structure:
	#   - add_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

add_rand__prologue:
	begin
	push 	$ra
	push	$s0
	# TODO: add code to set up your stack frame here

add_rand__body:
	move 	$s0, $a0	# save value into stack

	li 	$a0, 0xFFFF
	jal 	rand		# rand(0xFFFF)
	add	$v0, $v0, $s0	# return value + rand(0xFFFF)

	# TODO: complete your function body here

add_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop	$s0
	pop	$ra
	end

	jr	$ra


########################################################################
# .TEXT <sub_rand>
	.text
sub_rand:
	# Args:
	#   - $a0: int value
	# Returns: int
	#
	# Frame:	[$s0, $ra]
	# Uses: 	[$s0, $ra, $v0, $a0]
	# Clobbers:	[$a0, $v0]
	#
	# Locals:	
	#	- $s0: int value
	#
	# Structure:
	#   - sub_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

sub_rand__prologue:
	begin
	push 	$ra
	push 	$s0

	# TODO: add code to set up your stack frame here

sub_rand__body:

	move 	$s0, $a0	# saves int value into stack 

	jal	rand		# rand(value)
	sub	$v0, $s0, $v0	# return value - return(value)
	# TODO: complete your function body here

sub_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop 	$s0
	pop	$ra
	end

	jr	$ra

########################################################################
# .TEXT <seq_rand>
	.text
seq_rand:
	# Args:
	#   - $a0: int value
	# Returns: int value
	#
	# Frame:	[$ra, $s0, $s1, $s2]
	# Uses: 	[$ra, $s0, $s1, $s2, $v0, $a0]
	# Clobbers:	[$v0, $a0]
	#
	# Locals:
	#   - $s0: int value
	#   - $s1: int limit
	#   - $s2: int i
	#
	# Structure:
	#   - seq_rand
	#     -> [prologue]
	#     -> [body]
	#     -> [epilogue]

seq_rand__prologue:
	begin
	push	$ra
	push 	$s0
	push 	$s1
	push	$s2

	# TODO: add code to set up your stack frame here

seq_rand__body:

	move 	$s0, $a0
	
	li	$a0, 100	# int limit = rand(100)
	jal	rand
	move	$s1, $v0	

	seq_rand__loop_init:		# Note to self, even with  loops,  if function calling, then use save registers
		li	$s2, 0	# int i = 0
	seq_rand__loop_cond:
		bge	$s2, $s1, seq_rand__loop_epilogue 	# while(i < limit)
	seq_rand__loop_body:

		move	$a0, $s0	# value = add_rand(value)
		jal	add_rand	#
		move	$s0, $v0	#

	seq_rand__loop_increment:
		addi	$s2, $s2, 1	# i = i + 1
		j	seq_rand__loop_cond
		
	seq_rand__loop_epilogue:
		move 	$v0, $s0
	# TODO: complete your function body here

seq_rand__epilogue:
	
	# TODO: add code to clean up stack frame here
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
	
	jr	$ra



##
## The following are two utility functions, provided for you.
##
## You don't need to modify any of the following,
## but you may find it useful to read through.
## You'll be calling these functions from your code.
##

OFFLINE_SEED = 0x7F10FB5B

########################################################################
# .DATA
	.data
	
# int random_seed;
	.align 2
random_seed:
	.space 4


########################################################################
# .TEXT <seed_rand>
	.text
seed_rand:
# DO NOT CHANGE THIS FUNCTION

	# Args:
	#   - $a0: unsigned int seed
	# Returns: void
	#
	# Frame:	[]
	# Uses:		[$a0, $t0]
	# Clobbers:	[$t0]
	#
	# Locals:
	#   - $t0: offline_seed
	#
	# Structure:
	#   - seed_rand

	li	$t0, OFFLINE_SEED		# const unsigned int offline_seed = OFFLINE_SEED;
	xor	$t0, $a0			# random_seed = seed ^ offline_seed;
	sw	$t0, random_seed

	jr	$ra				# return;

########################################################################
# .TEXT <rand>
	.text
rand:
# DO NOT CHANGE THIS FUNCTION

	# Args:
	#   - $a0: unsigned int n
	# Returns:
	#   - $v0: int
	#
	# Frame:    []
	# Uses:     [$a0, $v0, $t0]
	# Clobbers: [$v0, $t0]
	#
	# Locals:
	#   - $t0: int rand
	#
	# Structure:
	#   - rand

	lw	$t0, random_seed 		# unsigned int rand = random_seed;
	multu	$t0, 0x5bd1e995  		# rand *= 0x5bd1e995;
	mflo	$t0
	addiu	$t0, 12345       		# rand += 12345;
	sw	$t0, random_seed 		# random_seed = rand;

	remu	$v0, $t0, $a0    
	jr	$ra              		# return rand % n;
