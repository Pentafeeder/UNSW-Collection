# COMP1521 20T3 final exam Q9 starter code

# MIPS below implements C function main
# do not change the MIPS

# int main(void) {
#     int size;
#     scanf("%d", &size);
#     int array[size];
#     read_array(size, array);
#     sort(size, array);
#     print_array(size, array);
# }

# register $s0 used for variable size
# register $s1 used for address of array
# register $t0 used for temporary calculations

main:
    addi $sp, $sp, -12    # save registers on stack
    sw   $ra, 12($sp)
    sw   $s0, 8($sp)
    sw   $s1, 4($sp)

    li   $v0, 5         # scanf("%d", &size);
    syscall
    move $s0, $v0

    mul  $t0, $s0, 4    #  allocate space for array
    sub  $sp, $sp, $t0
    addi $s1, $sp, 4

    move $a0, $s0       # read_array(size, array);
    move $a1, $s1
    jal read_array

    move $a0, $s0       # sort(size, array);
    move $a1, $s1
    jal sort

    move $a0, $s0       # print_array(size, array);
    move $a1, $s1
    jal print_array

    mul  $t0, $s0, 4    # deallocate space for array
    add  $sp, $sp, $t0

    lw   $ra, 12($sp)
    lw   $s0, 8($sp)
    lw   $s1, 4($sp)
    addi $sp, $sp, 12

    li   $v0, 0
    jr   $ra


# DO NOT CHANGE CODE ABOVE HERE


# The MIPS you write below should implement the C function sort

# void sort(int n, int a[]) {
#     if (n > 1) {
#       int p = partition(n, a);
#       sort(p, a);
#       sort(n - (p + 1), a + p + 1);
#     }
# }

sort:

sort_prologue:
	begin
	push	$ra
	push	$s0
	push	$s1
	push	$s2
sort_body:
	move	$s0, $a0	
	move 	$s1, $a1

	ble	$s0, 1, sort_epilogue	# if (n > 1)

	jal	partition		# int p  = partition(n, a)
	move	$s2, $v0
	
	move	$a0,  $s2		# sort(p, a)
	move	$a1, $s1
	jal	sort
	
	add	$t0, $s2, 1		#sort(n - (p + 1), a + p + 1)
	sub 	$t0, $s0, $t0
	move	$a0, $t0

	add	$t0, $s2, 1
	mul	$t0, $t0, 4
	add	$t0, $s1, $t0
	move	$a1, $t0
	jal	sort

sort_epilogue:
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
    	jr $ra


# The MIPS you write below should implement the C function partition

# int partition(int n, int a[]) {
#     int pivot_value = a[n - 1];
#     int i = 0;
#     for (int j = 0; j < n; j++) {
#         if (a[j] < pivot_value) {
#           swap(&a[i], &a[j]);
#           i = i + 1;
#         }
#     }
#   swap(&a[i], &a[n - 1]);
#   return i;
# }

partition:
	# $t0: temporary value
	# $s0: int n
	# $s1: int a[]
	# $s2: int i
	# $s3: int j
	# $s4: int pivot_value

partition_prologue:
	begin
	push	$ra
	push	$s0
	push	$s1
	push	$s2
	push	$s3
	push	$s4
partition_body:
	move	$s0, $a0
	move	$s1, $a1

	sub	$t0, $s0, 1	# int pivot_value = a[n - 1]
	mul	$t0, $t0, 4 	
	add	$t0, $s1, $t0
	lw	$s4, ($t0)
	
	li	$s2, 0
	
partition_loop_init:
	li	$s3, 0

partition_loop_cond:
	bge 	$s3, $s0, partition_loop_end

partition_loop_body:
	mul	$t0, $s3, 4
	add	$t0, $s1, $t0

	lw	$t1, ($t0)

	bge	$t1, $s4, partition_loop_step	# if (a[j] < pivot_value)

	mul	$t2, $s2, 4			# swap(&a[i], &a[j])
	add	$t2, $t2, $s1

	move	$a1, $t0
	move	$a0, $t2
	jal	swap

	addi	$s2, 1				# i = i + 1

partition_loop_step:
	addi	$s3, 1				# j = j + 1
	b	partition_loop_cond

partition_loop_end:
	mul	$t0, $s2, 4
	add	$t0, $t0, $s1

	sub	$t1, $s0, 1
	mul	$t1, $t1, 4
	add	$t1, $t1, $s1

	move	$a0, $t0
	move	$a1, $t1
	jal 	swap

	move	$v0, $s2
partition_epilogue:
	pop	$s4
	pop	$s3
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
	jr $ra



# The MIPS you write below should implement the C function swap

# void swap(int *x, int *y) {
#   int temp = *x;
#   *x = *y;
#   *y = temp;
# }
#

swap:

swap_prologue:
swap_body:

	
	lw	$t0, ($a0)
	lw	$t1, ($a1)
	sw	$t1, ($a0)
	sw	$t0, ($a1)
swap_epilogue:
	jr $ra


# DO NOT CHANGE CODE BELOW HERE


# MIPS below implements C function read_array
# do not change this MIPS code

# void read_array(int rows, int cols, int a[rows][cols]) {
#     for (int r = 0; r < rows; r++) {
#         for (int c = 0; c < cols; c++) {
#             scanf("%d", &a[r][c]);
#         }
#     }
# }

# register $a0 n
# register $a1 a

# register $t0 used for variable i
# register $t1 used to save n
# register $t2 used for temporary calculation

read_array:
    move $t1, $a0
    li   $t0, 0
ra_loop:
    bge  $t0, $t1, ra_end
    mul  $t2, $t0, 4
    add  $t2, $t2, $a1
    move $a0, $t2
    li   $v0, 5
    syscall
    sw   $v0, ($t2)
    addi $t0, $t0, 1
    j    ra_loop
ra_end:
    jr $ra


# MIPS below implements C function print_array
# do not change this MIPS code

# void print_array(int rows, int cols, int a[rows][cols]) {
#     for (int r = 0; r < rows; r++) {
#         for (int c = 0; c < cols; c++) {
#             printf("%d ", a[r][c]);
#         }
#         printf("\n");
#     }
# }

# register $a0 n
# register $a1 a

# register $t0 used for variable i
# register $t1 used to save n
# register $t2 used for temporary calculation

print_array:
    move $t1, $a0
    li   $t0, 0
pa_loop:
    bge  $t0, $t1, pa_end
    mul  $t2, $t0, 4
    add  $t2, $t2, $a1
    lw   $a0, ($t2)
    li   $v0, 1
    syscall
    li   $a0, ' '
    li   $v0, 11
    syscall
    addi $t0, $t0, 1
    j    pa_loop
pa_end:
    li   $a0, '\n'
    li   $v0, 11
    syscall
    jr $ra
