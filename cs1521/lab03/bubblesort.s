# Reads 10 numbers into an array, bubblesorts them
# and then prints the 10 numbers
# YOUR-NAME-HERE, DD/MM/YYYY

# Constants
ARRAY_LEN = 10

main:
	# Registers:
	#  - $t0: int i
	#  - $t1: temporary result
	#  - $t2: temporary result
	#  - $t3: int swapped
	#  - $t4: int x
	#  - $t5: int y

scan_loop__init:
	li	$t0, 0				# i = 0
scan_loop__cond:
	bge	$t0, ARRAY_LEN, scan_loop__end	# while (i < ARRAY_LEN) {

scan_loop__body:
	li	$v0, 5				#   syscall 5: read_int
	syscall					#
						#
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	sw	$v0, ($t2)			#   scanf("%d", &numbers[i]);

	addi	$t0, $t0, 1			#   i++;
	b	scan_loop__cond			# }
scan_loop__end:

	# TODO: add your code here!
swapped__init:
	li 	$t3, 1				# int swapped = 1
while_swapped:
	beqz	$t3, print_loop__init	# while (swapped)

sort_loop__init:
	li 	$t3, 0				# swapped = 0
	li 	$t0, 1				# i = 1
sort_loop__cond:
	bge	$t0, ARRAY_LEN, sort_loop__end	# while (i < ARRAY_LEN)
sort_loop__body:
	la 	$t2, numbers
	mul	$t1, $t0, 4
	add	$t2, $t2, $t1			# $numbers[i] = numbers + 4 * i

	lw	$t4, ($t2)			# int x = numbers[i]
	sub 	$t2, $t2, 4
	lw 	$t5, ($t2)			# int y = numbers[i - 1]

	bge	$t4, $t5, x_ge_y		# if (x < y)

	sw	$t4, ($t2)			# numbers[i - 1] = x
	addi	$t2, $t2, 4
	sw 	$t5, ($t2)			# numbers[i] = y
	li 	$t3, 1				# swapped = 1
x_ge_y:
	addi 	$t0, 1				# i++
	b	sort_loop__cond
sort_loop__end:
	b	while_swapped
	




print_loop__init:
	li	$t0, 0				# i = 0
print_loop__cond:
	bge	$t0, ARRAY_LEN, print_loop__end	# while (i < ARRAY_LEN) {

print_loop__body:
	mul	$t1, $t0, 4			#   calculate &numbers[i] == numbers + 4 * i
	la	$t2, numbers			#
	add	$t2, $t2, $t1			#
	lw	$a0, ($t2)			#
	li	$v0, 1				#   syscall 1: print_int
	syscall					#   printf("%d", numbers[i]);

	li	$v0, 11				#   syscall 11: print_char
	li	$a0, '\n'			#
	syscall					#   printf("%c", '\n');

	addi	$t0, $t0, 1			#   i++
	b	print_loop__cond		# }
print_loop__end:
	
	li	$v0, 0
	jr	$ra				# return 0;


	.data
numbers:
	.word	0:ARRAY_LEN			# int numbers[ARRAY_LEN] = {0};
