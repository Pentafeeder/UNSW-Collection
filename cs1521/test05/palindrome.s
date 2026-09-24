# Reads a line and prints whether it is a palindrome or not

LINE_LEN = 256

########################################################################
# .TEXT <main>
main:
	# Locals:
	#   - $t0: int i
	#   - $t1: temporary value
	#   - $t2: int j
	#   - $t3: int k
	#   - $t4: line[j]
	#   - $t5: line[k]
	#   - $t6: line[i]

	li	$v0, 4				# syscall 4: print_string
	la	$a0, line_prompt_str		#
	syscall					# printf("Enter a line of input: ");

	li	$v0, 8				# syscall 8: read_string
	la	$a0, line			#
	la	$a1, LINE_LEN			#
	syscall					# fgets(buffer, LINE_LEN, stdin)

	line_length_loop__init:
	li	$t0, 0				# int i = 0
	line_length_loop__cond:
	la	$t1, line			# &line[i] = line + i
	add	$t1, $t1, $t0			#
	lb	$t1, ($t1)			# $t1 = line[i]

	beqz	$t1, line_length_loop__end	# while (line[i] != 0)

	line_length_loop__body:
	line_length_loop__step:
	addi	$t0, 1				# i++
	b	line_length_loop__cond

	line_length_loop__end:

	j_lt_k_loop__init:
	li	$t2, 0				# int j = 0
	sub	$t3, $t0, 2			# int k = i - 2

	j_lt_k_loop__cond:
	bge	$t2, $t3, j_lt_k_loop__end	# while (j < k)
	
	j_lt_k_loop__body:
	la	$t1, line			
	add	$t4, $t2, $t1			# &line[j] = line + j
	add	$t5, $t3, $t1			# &line[k] = line + k

	lb	$t4, ($t4)			# $t4 = line[j]
	lb	$t5, ($t5)			# $t5 = line[k]

	beq	$t4, $t5, j_lt_k_loop__step	# if (line[j] != line[k])

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_not_palindrome_str	#
	syscall					# printf("not palindrome\n");
	b	epilogue
	
	j_lt_k_loop__step:
	addi	$t2, 1				# j++
	addi	$t3, -1				# k--
	b	j_lt_k_loop__cond

	j_lt_k_loop__end:
	

	li	$v0, 4				# syscall 4: print_string
	la	$a0, result_palindrome_str	#
	syscall					# printf("palindrome\n");

	epilogue:
	li	$v0, 0
	jr	$ra				# return 0;


########################################################################
# .DATA
	.data
# String literals
line_prompt_str:
	.asciiz	"Enter a line of input: "
result_not_palindrome_str:
	.asciiz	"not palindrome\n"
result_palindrome_str:
	.asciiz	"palindrome\n"

# Line of input stored here
line:
	.space	LINE_LEN

