# A simple program to manage student marks.
# YOUR-NAME-HERE, INSERT-DATE-HERE

#![tabsize(8)]

# Constant definitions.
# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

# NULL pointer
NULL = 0x00

# Constants for accessing `struct student`
STRUCT_STUDENT_ID_OFFSET = 0
STRUCT_STUDENT_MARK_OFFSET = STRUCT_STUDENT_ID_OFFSET + 4
SIZEOF_STRUCT_STUDENT = STRUCT_STUDENT_MARK_OFFSET + 4

# Other constants
CLASS_SIZE = 6
UNKNOWN_MARK = -1

################################################################################
# DATA SEGMENT
# !!! DO NOT ADD, REMOVE, MODIFY OR REORDER ANY OF THESE DEFINITIONS !!!
	.data
# Global variables	
students:			# struct student students[CLASS_SIZE] = {
	.word	5123456		#   { int id,
	.word	UNKNOWN_MARK	#    int mark },
	.word	5308310		#   { int id,
	.word	UNKNOWN_MARK	#     int mark },
	.word	5417087		#   { int id,
	.word	UNKNOWN_MARK	#     int mark },
	.word	3456789		#   { int id,
	.word	UNKNOWN_MARK	#     int mark },
	.word	5345678		#   { int id,
	.word	UNKNOWN_MARK	#     int mark },
	.word	5234567		#   { int id,
	.word	UNKNOWN_MARK	#     int mark }
				# };

# String literals
update_student_mark__id_prompt:
	.asciiz	"Please enter the student ID: "
update_student_mark__mark_prompt:
	.asciiz	"Please enter the student mark: "
update_student_mark__invalid_id:
	.asciiz	"Student not found in class!\n"
print_report__header:
	.asciiz	"ID\tMark\n"
print_report__unknown_mark:
	.asciiz	"?\n"

################################################################################
# You will need to complete the following functions below this line:
# - [X] find_student_by_id
# - [X] update_student_mark
# - [X] print_report
# Some of the above functions are partially implemented for you. You may choose 
# to complete the provided implementation, or you may choose to implement them
# yourself from scratch.
#
# The following function is provided for you. You should NOT modify it.
# - [X] main
################################################################################

################################################################################
# .TEXT find_student_by_id
	.text
find_student_by_id:
	# Args:
	#	- $a0: int id
	# Returns:
	#	- $v0: struct student *
	#
	# Stack:	[None]
	# Uses:		[$a0, $t1, $t2, $t3, $t4, $t0, $v0]
	# Clobbers:	[$t1, $t2, $t3, $t4, $t0, $v0]
	#
	# Locals:
	#	- $t0: int i
	#	- $t1: temporary value	(8 * i)
	#	- $t2: temporary value (&students)
	#	- $t3: $students[i]
	#	- $t4: students[i].id
	#	- $t5: int id
	#
	# Structure:
	#	-> [prologue]
	#	-> [body]
	#	  -> loop
	#	    -> [init]
	#	    -> [cond]
	#	    -> [body]
	#	    -> [step]
	#	    -> [end]
	#	-> [epilogue]
find_student_by_id__prologue:
	begin
	
find_student_by_id__body:
find_student_by_id__loop__init:
	li	$t0, 0						# int i = 0;
	move 	$t5, $a0
find_student_by_id__loop__cond:
	bge	$t0, CLASS_SIZE, find_student_by_id__loop__end	# while (i < CLASS_SIZE) {
find_student_by_id__loop__body:
	# TODO: implement the body of this loop
	

	mul	$t1, $t0, SIZEOF_STRUCT_STUDENT			# &student[i] = student + 8 * i
	la	$t2, students
	add	$t3, $t2, $t1	

	lw 	$t4, STRUCT_STUDENT_ID_OFFSET($t3)		# $t4 = students[i].id

	bne	$t5, $t4, find_student_by_id__loop__step	# if (students[i].id == id)
	
	

	move	$v0, $t3					# return &students[i]
	b	find_student_by_id__epilogue

find_student_by_id__loop__step:
	addi	$t0, 1						#  i++;
	j	find_student_by_id__loop__cond			# }

find_student_by_id__loop__end:
	li 	$v0, NULL

find_student_by_id__epilogue:
	end
	jr	$ra

################################################################################
# .TEXT update_student_mark
	.text
update_student_mark:
	# Args:		void
	# Returns:	void
	#
	# Stack:	[$ra, $s0]
	# Uses:		[$ra, $s0, $t0, $a0, $v0]
	# Clobbers:	[$t0, $a0, $v0]
	#
	# Locals:
	#	- $t0: struct student *student
	#	- $s0: int id
	#
	# Structure:
	#	-> [prologue]
	#	-> [body]
	#	-> [epilogue]
update_student_mark__prologue:
	begin
	push 	$ra
	push	$s0
update_student_mark__body:
	# TODO: complete this function
	# You may need to modify the prologue and epilogue of this function.
	li 	$v0, 4					#syscall 4: print string
	la	$a0, update_student_mark__id_prompt
	syscall						# printf("Please enter the student ID: ")

	li	$v0, 5					# syscall 5:  read int
	syscall
	move	$s0, $v0				#scanf("%d", &id)

	move	$a0, $s0
	jal	find_student_by_id
	move	$t0, $v0

	bne	$t0, NULL, student_not_null

	li	$v0, 4
	la	$a0, update_student_mark__invalid_id
	syscall
	
	b	update_student_mark__epilogue


student_not_null:
	li	$v0, 4
	la	$a0, update_student_mark__mark_prompt
	syscall

	li	$v0, 5
	syscall	
	
	sw	$v0, STRUCT_STUDENT_MARK_OFFSET($t0)

update_student_mark__epilogue:
	pop	$s0
	pop 	$ra
	end
	jr	$ra

################################################################################
# .TEXT print_report
	.text
print_report:
	# Args:		void
	# Returns:	void
	#
	# Stack:	[None]
	# Uses:		[$t1, $t2, $t3, $t4, $t5, $t0, $v0]
	# Clobbers:	[$t1, $t2, $t3, $t4, $t5, $t0, $v0]
	#
	# Locals:
	#	- $t0: int i
	#	- $t1: temporary value (4 * i)
	#	- $t2: temporary value (&students)
	#	- $t3: &students[i]
	#	- $t4: students[i].id
	#	- $t5: students[i].mark
	#
	# Structure:
	#	-> [prologue]
	#	-> [body]
	#	  -> loop
	#	    -> [init]
	#	    -> [cond]
	#	    -> [body]
	#		-> [student_mark_ne_unknown_mark]
	#	    -> [step]
	#	    -> [end]
	#	-> [epilogue]
print_report__prologue:
	begin
print_report__body:
	li	$v0, 4						# syscall 4: print string
	la	$a0, print_report__header			# 
	syscall							# printf("ID\tMark\n");

print_report__loop__init:
	li	$t0, 0						# int i = 0;
print_report__loop__cond:
	bge	$t0, CLASS_SIZE, print_report__loop__end	# while (i < CLASS_SIZE) {
print_report__loop__body:
	# TODO: implement the body of this loop
	mul	$t1, $t0, SIZEOF_STRUCT_STUDENT			# by 8 since sizeof(struct students) = 8
	la	$t2, students
	add	$t3, $t2, $t1

	lw	$t4, STRUCT_STUDENT_ID_OFFSET($t3)
	
	li	$v0, 1						# syscall 1: print int
	move	$a0, $t4					# 
	syscall							# printf("%d")

	li	$v0, 11	
	li	$a0, '\t'
	syscall
	
	lw	$t5, STRUCT_STUDENT_MARK_OFFSET($t3)
	
	bne	$t5, UNKNOWN_MARK, student_mark_ne_unknown_mark

	li	$v0, 4
	la	$a0, print_report__unknown_mark
	syscall
	
	b	print_report__loop__step

	student_mark_ne_unknown_mark:
		li	$v0, 1
		move	$a0, $t5
		syscall

		li	$v0, 11
		li	$a0, '\n'
		syscall

print_report__loop__step:
	addi	$t0, 1						#  i++;
	j	print_report__loop__cond			# }
	
print_report__loop__end:
print_report__epilogue:
	end
	jr	$ra

################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
# You should NOT edit any code below this line.
# Options for selection
OPTION_UPDATE_MARK = 1
OPTION_PRINT_REPORT = 2
OPTION_EXIT = 3

	.data
main__welcome_message:
	.asciiz	"=== Welcome to the Class Management System ===\n"
main__menu:
	.ascii	"Options:\n"
	.ascii	"1. Update student mark\n"
	.ascii	"2. Print class report\n"
	.ascii	"3. Exit\n"
	.asciiz	"Please select an option [1-3]: "
main__invalid_option:
	.asciiz	"Invalid option!\n"
main__exit_message:
	.asciiz	"=== Exiting cms. Goodbye! ===\n"
################################################################################
# .TEXT main
# YOU SHOULD NOT MODIFY THIS FUNCTION.
	.text
main:
	# Args:		void
	# Returns:	int
	#
	# Stack:	[$ra]
	# Uses:		[]
	# Clobbers:	[]
	#
	# Locals:
	#	- $t0: int option
	#
	# Structure:
	#	-> [prologue]
	#	-> [body]
	#	  -> option_loop
	#	    -> [body]
	#	      -> update_mark
	#	      -> print_report
	#	      -> exit
	#	   -> [end]
	#	-> [epilogue]

main__prologue:
	begin
	push	$ra

main__body:
	li	$v0, 4						# syscall 4: print_string
	la	$a0, main__welcome_message			#
	syscall							# printf("=== Welcome to the Class Management System ===\n");

main__option_loop__body:
	li	$v0, 4						# syscall 4: print_string
	la	$a0, main__menu					#
	syscall							# printf("Options:\n...");

	li	$v0, 5						# syscall 5: read_int
	syscall							# 
	move	$t0, $v0					# scanf("%d", &option);

	beq	$t0, OPTION_UPDATE_MARK , main__update_mark	# if (option == OPTION_UPDATE_MARK) goto main__update_mark;
	beq	$t0, OPTION_PRINT_REPORT, main__print_report	# if (option == OPTION_PRINT_REPORT) goto main__print_report;
	beq	$t0, OPTION_EXIT	, main__exit		# if (option == OPTION_EXIT) goto main__exit;

	li	$v0, 4						# syscall 4: print_string
	la	$a0, main__invalid_option			#
	syscall							# printf("Invalid option!\n");

	j	main__option_loop__body				# goto main__option_loop__body;

main__update_mark:
	jal	update_student_mark				# update_student_mark();
	j	main__option_loop__body				# goto main__option_loop__body;

main__print_report:
	jal	print_report					# print_report();
	j	main__option_loop__body				# goto main__option_loop__body;

main__exit:
	j	main__option_loop__end				# goto main__option_loop__end;

main__option_loop__end:
	li	$v0, 4						# syscall 4: print_string
	la	$a0, main__exit_message				#
	syscall							# printf("=== Exiting cms. Goodbye! ===\n");

main__epilogue:
	pop	$ra
	end

	li	$v0, 0
	jr	$ra						# return 0;
