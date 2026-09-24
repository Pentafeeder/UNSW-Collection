# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
# Kevin Le (z5481482), 19/06/2023

# Constants
ARRAY_LEN = 1000

#	Locals:
#		- $t0: int i
#		- $t1: int j
#		- $t2: temporary result
#		- $t3: temporary result
#		- $t4: prime[i]
#		- $t5: int j
main:

	# TODO: add your code here
i_lt_ARRAY_LEN__loop_init:
	li	$t0, 2

i_lt_ARRAY_LEN__loop_cond:
	bge	$t0, ARRAY_LEN, epilogue

i_lt_ARRAY_LEN__loop_body:
ith_prime_true:
	
	la	$t3, prime
	add	$t2, $t0, $t3

	lb 	$t4, ($t2)

	bne	$t4, 1, i_lt_ARRAY_LEN__loop_epilogue

	li	$v0, 1		#syscall 1: print int
	move	$a0, $t0
	syscall			#printf("%d", i)

	li	$v0, 11		#syscall 11: print char
	la	$a0, '\n'
	syscall			#printf("\n")

j_lt_ARRAY_LEN__loop_init:
	li	$t1, 2
	mul	$t1, $t1, $t0
	li	$t5, 0

j_lt_ARRAY_LEN__loop_cond:
	bge	$t1, ARRAY_LEN, i_lt_ARRAY_LEN__loop_epilogue
j_lt_ARRAY_LEN__loop_body:
	la	$t3, prime
	add	$t2, $t1, $t3

	sb	$t5, ($t2)

j_lt_ARRAY_LEN__loop_epilogue:
	add	$t1, $t0, $t1
	b	j_lt_ARRAY_LEN__loop_cond

i_lt_ARRAY_LEN__loop_epilogue:
	addi 	$t0, $t0, 1
	b	i_lt_ARRAY_LEN__loop_cond

epilogue:
	li	$v0, 0
	jr	$ra			# return 0;

	.data
prime:
	.byte	1:ARRAY_LEN		# uint8_t prime[ARRAY_LEN] = {1, 1, ...};
