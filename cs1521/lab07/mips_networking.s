# Reads a 4-byte value and reverses the byte order, then prints it

BYTE_MASK = 0xFF

########################################################################
# .TEXT <main>
main:
	# Locals:
	#	- $t0: int network_bytes
	#	- $t1: int computer_bytes
	#	- $t2: uint32_t byte_mask 
	#	- $t3: temporary value


	li	$v0, 5		# scanf("%d", &network_bytes);
	syscall
	

	#
	# Your code here!
	#
	move	$t0, $v0

	li	$t1, 0
	li	$t2, BYTE_MASK 

	and 	$t3, $t0, $t2	# computer_bytes |= (network_bytes & byte_mask) << 24
	sll	$t3, 24
	or	$t1, $t1, $t3

	sll	$t3, $t2, 8	# computer_bytes |= (network_bytes & (byte_mask << 8)) << 8
	and	$t3, $t0, $t3
	sll	$t3, 8		
	or	$t1, $t1, $t3

	sll	$t3, $t2, 16	# computer_bytes |= (network_bytes & (byte_mask << 16)) >> 8
	and	$t3, $t0, $t3
	sra	$t3, 8
	or	$t1, $t1, $t3

	sll	$t3, $t2, 24	# computer_bytes |= (network_bytes & (byte_mask << 24)) >> 24
	and	$t3, $t0, $t3
	sra	$t3, 24
	or	$t1, $t1, $t3


	move	$a0, $t1	# printf("%d", computer_bytes);
	li	$v0, 1
	syscall

	li	$v0, 11
	li	$a0, '\n'
	syscall

main__end:
	li	$v0, 0		# return 0;
	jr	$ra


