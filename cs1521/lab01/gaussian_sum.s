# A simple MIPS program that calculates the Gaussian sum between two numbers

# int main(void)
# {
#   int number1, number2;
#
#   printf("Enter first number: ");
#   scanf("%d", &number1);
#
#   printf("Enter second number: ");
#   scanf("%d", &number2);
#
#   int gaussian_sum = ((number2 - number1 + 1) * (number1 + number2)) / 2;
#
#   printf("The sum of all numbers between %d and %d (inclusive) is: %d\n", number1, number2, gaussian_sum);
#
#   return 0;
# }

main:

  #
  # TODO: add your code HERE
  #	t0: num1
  #	t1: num2
  # 	t2: LHS operation
  #	t3: RHS operation
  #	t4: sum

	li	$v0, 4  	# print prompt msg1: "Enter first number: "
	la	$a0, prompt1
	syscall

	li	$v0, 5		#get user input and store in register t0
	syscall
	move	$t0, $v0

	li 	$v0, 4		#print prompt msg2: "Enter second number: "
	la	$a0, prompt2
	syscall

	li	$v0, 5		#get user input and store in register t1
	syscall
	move	$t1, $v0

	li	$v0, 4		#print prompt msg3: "The sum of all numbers between: "
	la	$a0, answer1
	syscall

	li	$v0, 1 		#print first integer from register t0 
	move 	$a0, $t0
	syscall

	li	$v0, 4		#print prompt msg4: "and "
	la 	$a0, answer2
	syscall

	li	$v0, 1		#pxrint second integer from register t1
	move	$a0, $t1
	syscall

	li 	$v0, 4		#print prompt msg5: "(inclusive) is: "
	la	$a0, answer3
	syscall

	
	sub 	$t2, $t1, $t0	#number2 - number1, stored in t2
	addi	$t2, $t2, 1 	#t2 + 1, stored in t2

	add 	$t3, $t1, $t0 	#number1 + number2, stored in t3

	mul	$t4, $t2, $t3	#multiply t3 and t2, then store in t4

	div 	$t4, $t4, 2	#divide result from t4 by 2 and store in same register

	li 	$v0, 1		#print sum value
	move 	$a0, $t4
	syscall 

	li 	$v0, 11		#print new line
	la	$a0, '\n'
	syscall

	li	$v0, 0
	jr	$ra          # return 0 


.data
  prompt1: .asciiz "Enter first number: "
  prompt2: .asciiz "Enter second number: "

  answer1: .asciiz "The sum of all numbers between "
  answer2: .asciiz " and "
  answer3: .asciiz " (inclusive) is: "
