########################################################################
# COMP1521 23T2 -- Assignment 1 -- Pacman!
#
#
# !!! IMPORTANT !!!
# Before starting work on the assignment, make sure you set your tab-width to 8!
# It is also suggested to indent with tabs only.
# Instructions to configure your text editor can be found here:
#   https://cgi.cse.unsw.edu.au/~cs1521/23T2/resources/mips-editors.html
# !!! IMPORTANT !!!
#
#
# This program was written by Kevin Le (z5481482)
# on 18/06/2023. This is a game of Pacman written using MIPS
#
# Version 1.0 (12-06-2023): Team COMP1521 <cs1521@cse.unsw.edu.au>
#
########################################################################

#![tabsize(8)]

# Constant definitions.
# !!! DO NOT ADD, REMOVE, OR MODIFY ANY OF THESE DEFINITIONS !!!

# Bools
FALSE = 0
TRUE  = 1

# Directions
LEFT  = 0
UP    = 1
RIGHT = 2
DOWN  = 3
TOTAL_DIRECTIONS = 4

# Map
MAP_WIDTH  = 13
MAP_HEIGHT = 10
MAP_DOTS   = 53
NUM_GHOSTS = 3

WALL_CHAR   = '#'
DOT_CHAR    = '.'
PLAYER_CHAR = '@'
GHOST_CHAR  = 'M'
EMPTY_CHAR  = ' '

# Other helpful constants
GHOST_T_X_OFFSET          = 0
GHOST_T_Y_OFFSET          = 4
GHOST_T_DIRECTION_OFFFSET = 8
SIZEOF_GHOST_T            = 12
SIZEOF_INT                = 4

########################################################################
# DATA SEGMENT
# !!! DO NOT ADD, REMOVE, MODIFY OR REORDER ANY OF THESE DEFINITIONS !!!

	.data
map:
	.byte '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'
	.byte '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'
	.byte '#', '.', '#', '#', '#', '#', '#', '#', '#', '#', '#', '.', '#'
	.byte '#', '.', '#', ' ', '#', '.', '.', '.', '.', '.', '.', '.', '#'
	.byte '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'
	.byte '#', '.', '.', '.', '.', '.', '#', '.', '#', '.', '.', '.', '#'
	.byte '#', '.', '#', '#', '#', '#', '#', '.', '#', '#', '#', '.', '#'
	.byte '#', '.', '#', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#'
	.byte '#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '#'
	.byte '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'

	.align 2
ghosts:
	.word 3, 3, UP		# ghosts[0]
	.word 4, 5, RIGHT	# ghosts[1]
	.word 9, 7, LEFT	# ghosts[2]

player_x:
	.word 7
player_y:
	.word 5

map_copy:
	.space	MAP_HEIGHT * MAP_WIDTH

	.align 2
valid_directions:
	.space	4 * TOTAL_DIRECTIONS
dots_collected:
	.word	0
x_copy:
	.word	0
y_copy:
	.word	0

lfsr_state:
	.space	4

# print_welcome strings
welcome_msg:
	.asciiz "Welcome to 1521 Pacman!\n"
welcome_msg_wall:
	.asciiz " = wall\n"
welcome_msg_you:
	.asciiz " = you\n"
welcome_msg_dot:
	.asciiz " = dot\n"
welcome_msg_ghost:
	.asciiz " = ghost\n"
welcome_msg_objective:
	.asciiz "\nThe objective is to collect all the dots.\n"
welcome_msg_wasd:
	.asciiz "Use WASD to move.\n"
welcome_msg_ghost_move:
	.asciiz "Ghosts will move every time you move.\nTouching them will end the game.\n"

# get_direction strings
choose_move_msg:
	.asciiz "Choose next move (wasd): "
invalid_input_msg:
	.asciiz "Invalid input! Use the wasd keys to move.\n"

	# main strings 
dots_collected_msg_1:
	.asciiz "You've collected "
dots_collected_msg_2:
	.asciiz " out of "
dots_collected_msg_3:
	.asciiz " dots.\n"

# check_ghost_collision strings
game_over_msg:
	.asciiz "You ran into a ghost, game over! :(\n"

# collect_dot_and_check_win strings
game_won_msg:
	.asciiz "All dots collected, you won! :D\n"


# ------------------------------------------------------------------------------
#                                 Text Segment
# ------------------------------------------------------------------------------

	.text

############################################################
####                                                    ####
####   Your journey begins here, intrepid adventurer!   ####
####                                                    ####
############################################################

################################################################################
#
# Implement the following functions,
# and check these boxes as you finish implementing each function.
#
#  SUBSET 0
#  - [X] print_welcome
#  SUBSET 1
#  - [X] main	   
#  - [X] get_direction
#  - [X] play_tick 
#  SUBSET 2
#  - [X] copy_map  
#  - [X] get_valid_directions 
#  - [X] print_map
#  - [X] try_move
#  SUBSET 3 -- remember to recheck registers for conventions
#  - [X] check_ghost_collision	
#  - [X] collect_dot_and_check_win
#  - [X] do_ghost_logic
#     (and also the ghosts part of print_map)
#  PROVIDED
#  - [X] get_seed
#  - [X] random_number


################################################################################
# .TEXT <print_welcome>
	.text
print_welcome:
	# Subset:   0
	#
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [None]
	# Uses:     [$a0, $v0]
	# Clobbers: [$a0, $v0]
	#
	# Locals: None
	#
	# Structure:
	#   print_welcome
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]

print_welcome__prologue:

print_welcome__body:
	li 	$v0, 4				# printf("Welcome to 1521 Pacman!\n")
	la 	$a0, welcome_msg		
	syscall					

	li 	$v0, 11				# printf("%c = wall\n", WALL_CHAR)
	la 	$a0, WALL_CHAR
	syscall
	li 	$v0, 4				
	la 	$a0, welcome_msg_wall		
	syscall	

	li 	$v0, 11				# printf("%c = you\n", PLAYER_CHAR)
	la 	$a0, PLAYER_CHAR
	syscall
	li 	$v0, 4				
	la 	$a0, welcome_msg_you		
	syscall

	li 	$v0, 11				# printf("%c = dot\n", DOT_CHAR)
	la 	$a0, DOT_CHAR
	syscall
	li 	$v0, 4				
	la 	$a0, welcome_msg_dot		
	syscall

	li 	$v0, 11				# printf("%c = ghost\n", DOT_CHAR)
	la 	$a0, GHOST_CHAR
	syscall
	li 	$v0, 4				
	la 	$a0, welcome_msg_ghost		
	syscall

	li	$v0, 4				# printf("\nThe objective is to collect all the dots.\n")
	la 	$a0, welcome_msg_objective	
	syscall		

	li	$v0, 4				# printf("Use WASD to move. \n")
	la 	$a0, welcome_msg_wasd		
	syscall		
	
	li	$v0, 4			
	la 	$a0, welcome_msg_ghost_move	# printf("Ghosts will move every time you move. \nTouching them will end the game. \n")
	syscall

print_welcome__epilogue:
	jr	$ra


################################################################################
# .TEXT <main>
	.text
main:
	# Subset:   1
	#
	# Args:     void
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [$ra]
	# Uses:     [$ra, $a0, $v0]
	# Clobbers: [$a0, $v0]
	#
	# Locals:  
	#   - $t0: &dots_collected
	#   - $t1: dots_collected
	#
	# Structure:
	#   main
	#   -> [prologue]
	#       -> body
	#	    -> play_tick__loop_body 
	#	    -> play_tick__loop_cond 
	#	    -> play_tick__loop_end
	#   -> [epilogue]

main__prologue:
	begin
	push 	$ra
main__body:
	jal	get_seed		# get_seed();
	jal	print_welcome		# print_welcome();

	play_tick__loop_body: 			# do:  
		jal	print_map			# print_map();
		
		li	$v0, 4				# printf("You've collected ")
		la	$a0, dots_collected_msg_1
		syscall

		la 	$t0, dots_collected		# $t0 = &dots_collected
		lw	$t1, ($t0)			# $t1 = dots_collected

		li	$v0, 1				# printf("%d", dots_collected)
		move	$a0, $t1
		syscall

		li 	$v0, 4				# printf(" out of ")
		la	$a0, dots_collected_msg_2
		syscall

		li	$v0, 1				# printf("%d", MAPS_DOTS)
		li	$a0, MAP_DOTS
		syscall

		li 	$v0, 4				# printf(" dots.\n")
		la	$a0, dots_collected_msg_3
		syscall

	play_tick__loop_cond: 
		move	$a0, $t0			# $v0 = play_tick(&dots_collected)
		jal 	play_tick			

		beq	$v0, TRUE, play_tick__loop_body	# while (play_tick(&dots_collected))
	play_tick__loop_end:

main__epilogue:	
	pop	$ra
	end
	li	$v0, 0
	jr	$ra


################################################################################
# .TEXT <get_direction>
	.text
get_direction:
	# Subset:   1
	#
	# Args:     void
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [None]
	# Uses:     [$a0, $v0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:   None 
	#
	# Structure:
	#   get_direction
	#   -> [prologue]
	#       -> body
	#	   -> while_input_true__loop_body
	#		-> check_input_eq_a
	#		-> check_input_eq_w
	#		-> check_input_eq_s
	#		-> check_input_eq_d
	#		-> check_input_eq_newline
	#		-> invalid_input_label
	#	   -> while_input_true__loop_epilogue
	#   -> [epilogue]

get_direction__prologue:

get_direction__body:
	li	$v0, 4				# printf("Choose next move (wasd): ")
	la	$a0, choose_move_msg
	syscall
	while_input_true__loop_body:
		li	$v0, 12			# int input = getchar()
		syscall
		
		check_input_eq_a:
			bne	$v0, 'a', check_input_eq_w 		# if (input == 'a')
			
			li	$v0, LEFT				# return LEFT
			b	get_direction__epilogue
		
		check_input_eq_w:		
			bne	$v0, 'w', check_input_eq_d 		# if (input == 'w') 
			
			li	$v0, UP					# return UP
			b	get_direction__epilogue
		
		check_input_eq_d:
			bne	$v0, 'd', check_input_eq_s 		# if (input == 'd')
			
			li	$v0, RIGHT				# return RIGHT
			b	get_direction__epilogue
		
		check_input_eq_s:
			bne	$v0, 's', check_input_eq_newline 	# if (input == 's')
			
			li	$v0, DOWN				# return DOWN
			b	get_direction__epilogue
		
		check_input_eq_newline:
			bne	$v0, '\n', invalid_input_label		# if (input == '\n')
			
			b	while_input_true__loop_body		# continue
		
		invalid_input_label:
		li	$v0, 4				# printf("Invalid input! Use the wasd keys to move.\n")
		la	$a0, invalid_input_msg
		syscall
		
		b	while_input_true__loop_body
	while_input_true__loop_epilogue:
	
	
get_direction__epilogue:
	jr	$ra


################################################################################
# .TEXT <play_tick>
	.text
play_tick:
	# Subset:   1
	#
	# Args:
	#    - $a0: int *dots_collected
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [$ra, $s0]
	# Uses:     [$ra, $s0, $v0, $a0, $a1, $a2]
	# Clobbers: [$v0, $a0, $a1, $a2]
	#
	# Locals:   None 
	#
	# Structure:
	#   play_tick
	#   -> [prologue]
	#       -> body
	#	    -> check_ghost_collision_true
	#	    -> call_do_ghost_logic
	#	    -> recheck_ghost_collision_true
	#	    -> return_negated
	#   -> [epilogue]

play_tick__prologue:
	begin	
	push	$ra
	push	$s0
play_tick__body:	
	move 	$s0, $a0			# save dots to $s0 (the value not address)

	jal	get_direction			# $v0 = get_direction()

	la	$a0, player_x			# try_move(&player_x, &player_y, get_direction())
	la	$a1, player_y
	move	$a2, $v0
	jal	try_move

	check_ghost_collision_true:
		jal	check_ghost_collision		# if (check_ghost_collision() == 0)
		beqz	$v0, call_do_ghost_logic

		li	$v0, FALSE			# return FALSE
		b	play_tick__epilogue

	call_do_ghost_logic:
		jal	do_ghost_logic			# do_ghost_collision()

	recheck_ghost_collision_true:
		jal	check_ghost_collision		# if (check_ghost_collision() == 0)
		beqz	$v0, call_collect_dot_and_check_win
		
		li	$v0, FALSE			# return FALSE
		b	play_tick__epilogue

	call_collect_dot_and_check_win:			# return !collect_dot_and_check_win(dots)
		move	$a0, $s0			
		jal	collect_dot_and_check_win

		beqz	$v0, return_negated		# if (collect_dot_and_check_win(dots) == 0) {return 1}
		
		li	$v0, 0				# else {return 0}
		b	play_tick__epilogue

	return_negated:
		li	$v0, 1				
		
play_tick__epilogue:
	pop	$s0
	pop	$ra
	end
	jr	$ra


################################################################################
# .TEXT <copy_map>
	.text
copy_map:
	# Subset:   2
	#
	# Args:
	#    - $a0: char dst[MAP_HEIGHT][MAP_WIDTH]
	#    - $a1: char src[MAP_HEIGHT][MAP_WIDTH]
	#
	# Returns:  void
	#
	# Frame:    [None]
	# Uses:     [$t0, $t1, $t2, $t3, $t4, $a0, $a1]
	# Clobbers: [$t0, $t1, $t2, $t3, $t4]
	#
	# Locals:
	#   - $t0: int i
	#   - $t1: int j
	#   - $t2: &dst[i][j]
	#   - $t3: &src[i][j]
	#   - $t4: src[i][j]
	#
	# Structure:
	#   copy_map
	#   -> [prologue]
	#       -> body
	#	    -> i_lt_MAP_HEIGHT__loop_init
	#	    -> i_lt_MAP_HEIGHT__loop_cond
	#	    -> i_lt_MAP_HEIGHT__loop_body
	#		-> j_lt_MAP_WIDTH__loop_init
	#		-> j_lt_MAP_WIDTH__loop_cond
	#		-> j_lt_MAP_WIDTH__loop_body
	#		-> j_lt_MAP_WIDTH__loop_step
	#		-> j_lt_MAP_WIDTH__loop_end
	#	    -> i_lt_MAP_HEIGHT__loop_step
	#	    -> i_lt_MAP_HEIGHT__loop_end
	#   -> [epilogue]

copy_map__prologue:
	
copy_map__body:

	i_lt_MAP_HEIGHT__loop_init: 
		li	$t0, 0						# int i = 0
	i_lt_MAP_HEIGHT__loop_cond:
		bge	$t0, MAP_HEIGHT, i_lt_MAP_HEIGHT__loop_end	# while (i < MAP_HEIGHT)

	i_lt_MAP_HEIGHT__loop_body:
		j_lt_MAP_WIDTH__loop_init:	
			li	$t1, 0						# int j = 0
		j_lt_MAP_WIDTH__loop_cond:
			bge	$t1, MAP_WIDTH, j_lt_MAP_WIDTH__loop_end	# while (j < MAP_WIDTH)
		
		j_lt_MAP_WIDTH__loop_body:
			mul	$t2, $t0, MAP_WIDTH				# &dst[i][j] = dst + i * MAP_WIDTH + j
			add	$t2, $a0, $t2			
			add	$t2, $t2, $t1			

			mul	$t3, $t0, MAP_WIDTH				# &src[i][j] = src + i * MAP_WIDTH + j
			add	$t3, $a1, $t3
			add	$t3, $t3, $t1	

			lb	$t4, ($t3)					# $t4 = src[i][j]
			sb	$t4, ($t2)					# dst[i][j] = src[i][j]
			
		j_lt_MAP_WIDTH__loop_step:
			addi	$t1, 1						# j++
			b	j_lt_MAP_WIDTH__loop_cond		
		j_lt_MAP_WIDTH__loop_end:

	i_lt_MAP_HEIGHT__loop_step:
		addi 	$t0, 1						# i++
		b	i_lt_MAP_HEIGHT__loop_cond
	i_lt_MAP_HEIGHT__loop_end:
copy_map__epilogue:
	jr	$ra


################################################################################
# .TEXT <get_valid_directions>
	.text
get_valid_directions:
	# Subset:   2
	#
	# Args:
	#    - $a0: int x
	#    - $a1: int y
	#    - $a2: int dir_array[TOTAL_DIRECTIONS]
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [$ra, $s0, $s1, $s2]
	# Uses:     [$ra, $s0, $s1, $s2, $t0, $t1, $t2, $t3, $t4, $a0, $a1, $a2, $v0]
	# Clobbers: [$t0, $t1, $t2, $t3, $a0, $a1, $a2, $v0]
	#
	# Locals:
	#   - $s0: int x
	#   - $s1: int y
	#   - $s2: int dir_arrays[TOTAL_DIRECTIONS]
	#   - $s3: int dir
	#   - $s4: int valid_dirs
	#   - $t1: &x_copy
	#   - $t2: &y_copy
	#   - $t3: dir_array[valid_dirs]
	#
	# Structure:
	#   get_valid_directions
	#   -> [prologue]
	#       -> body
	#	   -> dir_lt_TOTAL_DIRECTIONS__loop_init
	#	   -> dir_lt_TOTAL_DIRECTIONS__loop_cond
	#	   -> dir_lt_TOTAL_DIRECTIONS__loop_body 
	#	   -> dir_lt_TOTAL_DIRECTIONS__loop_step 
	#	   -> dir_lt_TOTAL_DIRECTIONS__loop_end 
	#   -> [epilogue]

get_valid_directions__prologue:
	begin
	push	$ra
	push	$s0
	push	$s1
	push	$s2
	push	$s3
	push	$s4

get_valid_directions__body:
	move	$s0, $a0				
	move	$s1, $a1
	move	$s2, $a2

	li	$s4, 0				# int valid_dirs = 0

	dir_lt_TOTAL_DIRECTIONS__loop_init:	
		li	$s3, 0						# int dirs = 0

	dir_lt_TOTAL_DIRECTIONS__loop_cond:
		bge	$s3, TOTAL_DIRECTIONS, dir_lt_TOTAL_DIRECTIONS__loop_end	# while (dir < TOTAL_DIRECTIONS)

	dir_lt_TOTAL_DIRECTIONS__loop_body:
		la	$t1, x_copy					# $t1 = &x_copy 
		la	$t2, y_copy					# $t2 = &y_copy
		
		sw	$s0, ($t1)					# x_copy = int x
		sw	$s1, ($t2)					# y_copy = int y


		move	$a0, $t1					# try_move(&x_copy, &y_copy, dir)
		move	$a1, $t2
		move	$a2, $s3
		jal	try_move

		beqz	$v0, dir_lt_TOTAL_DIRECTIONS__loop_step		# if (try_move(&x_copy, &y_copy, dir) == 1)
		
		mul	$t3, $s4, 4					# dir_array[valid_dirs] = dir
		add	$t3, $t3, $s2
		sw	$s3, ($t3)

		addi	$s4, 1						# valid_dirs++

	dir_lt_TOTAL_DIRECTIONS__loop_step:	
		addi	$s3, 1						# dir++
		b	dir_lt_TOTAL_DIRECTIONS__loop_cond

	dir_lt_TOTAL_DIRECTIONS__loop_end:
	
	move	$v0, $s4			# return valid_dirs

get_valid_directions__epilogue:
	pop	$s4
	pop	$s3
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
	jr	$ra


################################################################################
# .TEXT <print_map>
	.text
print_map:
	# Subset:   2
	#
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [$ra]
	# Uses:     [$ra, $a0, $v0, $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7]
	# Clobbers: [$a0, $v0, $t0, $t1, $t2, $t3, $t4, $t5, $t6, $t7]
	#
	# Locals:
	#   - $t0: &map_copy
	#   - $t1: int i
	#   - $t2: int j
	#   - $t3: $ghosts
	#   - $t4: temporary value
	#   - $t5: temporary value
	#   - $t6: temporary value
	#   - $t7: &map_copy[ghosts[i].y][ghosts[i].x]
	#
	# Structure:
	#   print_map
	#   -> [prologue]
	#       -> body
	#	    -> i_lt_NUM_GHOSTS__loop_init
	#	    -> i_lt_NUM_GHOSTS__loop_cond
	#	    -> i_lt_NUM_GHOSTS__loop_body
	#	    -> i_lt_NUM_GHOSTS__loop_step
	#	    -> i_lt_NUM_GHOSTS__loop_end
	#	    -> print_MAP_HEIGHT__loop_init
	#	    -> print_MAP_HEIGHT__loop_cond
	#	    -> print_MAP_HEIGHT__loop_body
	#		-> print_MAP_WIDTH__loop_init
	#		-> print_MAP_WIDTH__loop_cond
	#		-> print_MAP_WIDTH__loop_body
	#		-> print_MAP_WIDTH__loop_step
	#		-> print_MAP_WIDTH__loop_end
	#	    -> print_MAP_HEIGHT__loop_step
	#	    -> print_MAP_HEIGHT__loop_end
	#   -> [epilogue]

print_map__prologue:
	begin
	push	$ra
print_map__body:
	la	$a0, map_copy
	la	$a1, map
	jal	copy_map

	la	$t0, map_copy					
	lw	$t4, player_y
	lw	$t5, player_x
	
	mul	$t4, $t4, MAP_WIDTH		# &map_copy[player_y][player_x] = map_copy + player_y * 4 + player_x
	add	$t4, $t0, $t4					
	add	$t4, $t4, $t5					

	li	$t5, PLAYER_CHAR
	sb	$t5, ($t4)			# map_copy[player_y][player_x] = PLAYER_CHAR
	
	# put ghosts on map
	i_lt_NUM_GHOSTS__loop_init:
		li	$t1, 0				# int i = 0
		la	$t3, ghosts			# $t3 = &ghosts

	i_lt_NUM_GHOSTS__loop_cond:
		bge	$t1, NUM_GHOSTS, i_lt_NUM_GHOSTS__loop_end	# while (i < NUM_GHOSTS)

	i_lt_NUM_GHOSTS__loop_body:
		mul	$t4, $t1, SIZEOF_GHOST_T	# $t4 = ghosts[i] = ghosts + SIZE_OF_GHOST_T * i   # &map_copy[ghosts[i].y][ghosts[i].x] = map_copy + (&ghosts + i * 4 + y_offset * MAP_WIDTH) + &ghosts + i * 4 +  x_offset
		add	$t4, $t4, $t3

		lw	$t5, GHOST_T_Y_OFFSET($t4)	# $t5 = ghosts[i].y * MAP_WIDTH
		mul	$t5, $t5, MAP_WIDTH

		
		lw	$t6, GHOST_T_X_OFFSET($t4)	# $t6 = ghosts[i].x 

		move	$t7, $t0			# $t7 = &map_copy[ghosts[i].y][ghosts[i].x]
		add	$t7, $t7, $t6			#     = map_copy + $t6 + $t5
		add	$t7, $t7, $t5

		li 	$t4, GHOST_CHAR
		sb	$t4, ($t7)			# map_copy[ghosts[i].y][ghosts[i].x] = GHOST_CHAR
	
	i_lt_NUM_GHOSTS__loop_step:
		addi	$t1, 1				#  i++
		b	i_lt_NUM_GHOSTS__loop_cond

	i_lt_NUM_GHOSTS__loop_end:

	# print the map
	print_MAP_HEIGHT__loop_init:
		li	$t1, 0						# int i = 0

	print_MAP_HEIGHT__loop_cond:
		bge	$t1, MAP_HEIGHT, print_MAP_HEIGHT_loop_end	# while (i < MAP_HEIGHT)

	print_MAP_HEIGHT__loop_body:

		print_MAP_WIDTH__loop_init:
			li	$t2, 0						#int j = 0

		print_MAP_WIDTH__loop_cond:
			bge	$t2, MAP_WIDTH, print_MAP_WIDTH__loop_end	# while (j <  MAP_WIDTH)

		print_MAP_WIDTH__loop_body:
			mul	$t3, $t1, MAP_WIDTH				# &map_copy[i][j] = map_copy + i * MAP_WIDTH + j
			add	$t3, $t3, $t0				
			add	$t4, $t3, $t2				

			
			li	$v0, 11						# putchar(map_copy[i][j])
			lb	$a0, ($t4)				
			syscall

		print_MAP_WIDTH__loop_step:
			addi	$t2, 1						# j++
			b	print_MAP_WIDTH__loop_cond

		print_MAP_WIDTH__loop_end:
		
		li	$v0, 11						# putchar('\n')
		li	$a0, '\n'
		syscall

	print_MAP_HEIGHT__loop_step:	
		addi	$t1, 1						# i++
		b	print_MAP_HEIGHT__loop_cond

	print_MAP_HEIGHT_loop_end:

print_map__epilogue:
	pop	$ra
	end
	jr	$ra


################################################################################
# .TEXT <try_move>
	.text
try_move:
	# Subset:   2
	#
	# Args:
	#    - $a0: int *x
	#    - $a1: int *y
	#    - $a2: int directions
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [None]
	# Uses:     [$t0, $t1, $t2, $t3, $a0, $a1, $a2]
	# Clobbers: [$t0, $t1, $t2, $t3, $a0, $a1]
	#
	# Locals:
	#   - $t0: int new_x
	#   - $t1: int new_y
	#   - $t2: temporary value 
	#   - $t3: &map[new_y][new_x]
	#
	# Structure:
	#   try_move
	#   -> [prologue]
	#       -> body
	#	    -> check_direction_eq_LEFT
	#	    -> check_direction_eq_UP
	#	    -> check_direction_eq_RIGHT
	#	    -> check_direction_eq_DOWN
	#	    -> check_map_coords_eq_WALL_CHAR
	#		-> return_FALSE
	#	    -> else_return_TRUE
	#   -> [epilogue]

try_move__prologue:
	lw	$t0, ($a0)			# int new_x = *x
	lw	$t1, ($a1)			# int new_y = *y
try_move__body:

	check_direction_eq_LEFT:
		bne	LEFT, $a2, check_direction_eq_UP		# if (direction == LEFT)
		addi	$t0, -1						# new_x--
		b	check_map_coords_eq_WALL_CHAR

	check_direction_eq_UP:
		bne	UP, $a2, check_direction_eq_RIGHT		# else if (direction == UP)
		addi	$t1, -1						# new_y--
		b	check_map_coords_eq_WALL_CHAR

	check_direction_eq_RIGHT:
		bne	RIGHT, $a2, check_direction_eq_DOWN		# else if (direction == RIGHT)
		addi	$t0, 1						# new_x++
		b	check_map_coords_eq_WALL_CHAR

	check_direction_eq_DOWN:
		bne	DOWN, $a2, check_map_coords_eq_WALL_CHAR	# else if (direction == DOWN)
		addi	$t1, 1						# new_y++

	check_map_coords_eq_WALL_CHAR:
		la 	$t2, map					# &map[new_y][new_x] = map + new_y * MAP_WIDTH + new_x
		mul	$t3, $t1, MAP_WIDTH
		add	$t3, $t3, $t2
		add	$t3, $t3, $t0

		lb	$t2, ($t3)					
		bne	$t2, WALL_CHAR, else_return_TRUE			# if (map[new_y][new_x] == WALL_CHAR)

		return_FALSE:
		li	$v0, FALSE					# return FALSE
		b	try_move__epilogue

	else_return_TRUE:
	sw	$t0, ($a0)					# *x = new_x
	sw	$t1, ($a1)					# *y = new_y
	li	$v0, TRUE					# return TRUE

try_move__epilogue:
	jr	$ra


################################################################################
# .TEXT <check_ghost_collision>
	.text
check_ghost_collision:
	# Subset:   3
	#
	# Args:     void
	# Returns:
	#    - $v0: int
	#
	# Frame:    [None]
	# Uses:     [$t0, $t1, $t2, $t3, $t4, $t5, $t6, $a0, $v0]
	# Clobbers: [$t0, $t1, $t2, $t3, $t4, $t5, $t6, $a0, $v0]
	#
	# Locals:
	#   - $t0: int i
	#   - $t1: player_x
	#   - $t2: player_y
	#   - $t3: &ghosts
	#   - $t4: &ghosts[i]
	#   - $t5: ghosts[i].x
	#   - $t6: ghosts[i].y
	#
	# Structure:
	#   check_ghost_collision
	#   -> [prologue]
	#       -> body
	#	    ->check_ghost_collision__loop_init
	#	    ->check_ghost_collision__loop_cond
	#	    ->check_ghost_collision__loop_body
	#		-> check_player_x_coord
	#		-> check_player_y_coord
	#		    -> game_over
	#	    ->check_ghost_collision__loop_step
	#	    ->check_ghost_collision__loop_end
	#   -> [epilogue]

check_ghost_collision__prologue:
	lw	$t1, player_x		
	lw	$t2, player_y
	la	$t3, ghosts

check_ghost_collision__body:

	check_ghost_collision__loop_init:
		li	$t0, 0						# int i = 0 

	check_ghost_collision__loop_cond:
		bge	$t0, NUM_GHOSTS, check_ghost_collision__loop_end	# while (i < NUM_GHOSTS)

	check_ghost_collision__loop_body:
		mul	$t4, $t0, SIZEOF_GHOST_T			# &ghosts[i] = ghosts + i * SIZE_OF_GHOST_T
		add	$t4, $t4, $t3

		lw	$t5, GHOST_T_X_OFFSET($t4)			# ghosts[i].x
		lw	$t6, GHOST_T_Y_OFFSET($t4)			# ghosts[i].y
		
		check_player_x_coord:
			bne	$t1, $t5, check_ghost_collision__loop_step	# if (player_x == ghosts[i].x &&
										#
		check_player_y_coord:						#
			bne	$t2, $t6, check_ghost_collision__loop_step	#     player_y == ghosts[i].y)

			game_over:
			li	$v0, 4						# printf("You ran into a ghosts, game over! :(\n")
			la	$a0, game_over_msg
			syscall
			
			li	$v0, TRUE					# return TRUE
			b	check_ghost_collision__epilogue

	check_ghost_collision__loop_step:
		addi	$t0, 1						# i++
		b	check_ghost_collision__loop_cond

	check_ghost_collision__loop_end:
	
	li	$v0, FALSE				# return FALSE

check_ghost_collision__epilogue:
	jr	$ra


################################################################################
# .TEXT <collect_dot_and_check_win>
	.text
collect_dot_and_check_win:
	# Subset:   3
	#
	# Args:
	#    - $a0: int *dots_collected
	#
	# Returns:
	#    - $v0: int
	#
	# Frame:    [None]
	# Uses:     [$a0, $v0, $t0, $t1, $t2, $t3, $t4]
	# Clobbers: [$a0, $v0, $t0, $t1, $t2, $t3, $t4]
	#
	# Locals:
	#   - $t0: player_x
	#   - $t1: player_y
	#   - $t2: char *map_char
	#   - $t3: temporary value
	#   - $t4: temporary value
	#
	# Structure:
	#   collect_dot_and_check_win
	#   -> [prologue]
	#       -> body
	#	    -> check_map_char_eq_DOT_CHAR
	#	        -> check_dots_eq_MAP_DOTS
	#		    -> game_won
	#	    -> did_not_win
	#   -> [epilogue]

collect_dot_and_check_win__prologue:
	lw	$t0, player_x
	lw	$t1, player_y

collect_dot_and_check_win__body:
	mul	$t2, $t1, MAP_WIDTH	# &map[player_y][player_x] = map + player_y  * MAP_WIDTH + player_x
	add	$t2, $t2, $t0
	la	$t3, map
	add	$t2, $t2, $t3

	lb	$t3, ($t2)		# char *map_char = &map[player_y][player_x]

	check_map_char_eq_DOT_CHAR:
		bne	$t3, DOT_CHAR, did_not_win	# if (*map_char == DOT_CHAR)
		
		li	$t4, EMPTY_CHAR			# *map_char = EMPTY_CHAR
		sb	$t4, ($t2)

		lw	$t4, ($a0)			# (*dots)++
		addi	$t4, 1				
		sw	$t4, ($a0)

		check_dots_eq_MAP_DOTS:
			bne	$t4, MAP_DOTS, did_not_win	# if (*dots == MAP_DOTS)

			game_won:
			li	$v0, 4				# printf("All dots collected, you won! :D\n")
			la	$a0, game_won_msg
			syscall

			li	$v0, TRUE			# return TRUE
			b	collect_dot_and_check_win__epilogue

	did_not_win:
	li	$v0, FALSE		# return FALSE

collect_dot_and_check_win__epilogue:
	jr	$ra


################################################################################
# .TEXT <do_ghost_logic>
	.text
do_ghost_logic:
	# Subset:   3
	#
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [$ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6]
	# Uses:     [$ra, $s0, $s1, $s2, $s3, $s4, $s5, $s6, $a0, $a1, $a2, $v0, $t0, $t1, $t2, $t3]
	# Clobbers: [$a0, $a1, $a2, $v0, $t0, $t1, $t2, $t3]
	#
	# Locals:
	#   - $s0: int ghost_id
	#   - $s1: &ghosts
	#   - $s2: &ghosts[ghost_id]
	#   - $s3: int n_valid_dirs
	#   - $s4: &ghosts[ghost_id].x
	#   - $s5: &ghosts[ghost_id].y
	#   - $s6: &ghosts[ghost_id].direction
	#   - $t0: temporary value
	#   - $t1: temporary value
	#   - $t2: temporary value
	#   - $t3: temporary value
	#
	# Structure:
	#   do_ghost_logic
	#   -> [prologue]
	#       -> body
	#	    -> ghost_id_lt_NUM_GHOSTS__loop_init
	#	    -> ghost_id_lt_NUM_GHOSTS__loop_cond
	#	    -> ghost_id_lt_NUM_GHOSTS__loop_body
	#		-> check_n_valid_dirs_eq_0
	#		-> check_whether_ghost_reached_decision_point
	#		    -> generate_new_direction
	#	    -> ghost_id_lt_NUM_GHOSTS__loop_step
	#	    -> ghost_id_lt_NUM_GHOSTS__loop_end
	#   -> [epilogue]

do_ghost_logic__prologue:
	begin
	push 	$ra
	push	$s0
	push	$s1
	push	$s2
	push	$s3
	push	$s4
	push	$s5
	push	$s6

do_ghost_logic__body:
	
	ghost_id_lt_NUM_GHOSTS__loop_init:
		li	$s0, 0					# int ghost_id = 0
		la	$s1, ghosts				# $s1 = &ghosts
	ghost_id_lt_NUM_GHOSTS__loop_cond:
		bge	$s0, NUM_GHOSTS, ghost_id_lt_NUM_GHOSTS__loop_end	# while (ghost_id < NUM_GHOSTS)

	ghost_id_lt_NUM_GHOSTS__loop_body:
		mul	$t0, $s0, SIZEOF_GHOST_T		# &ghosts[ghost_id]
		add	$s2, $t0, $s1					

		add	$s4, $s2, GHOST_T_X_OFFSET		# $s4 = &ghosts[ghost_id].x
		add	$s5, $s2, GHOST_T_Y_OFFSET		# $s5 = &ghosts[ghost_id].y
		add	$s6, $s2, GHOST_T_DIRECTION_OFFFSET	# $s6 = &ghosts[ghost_id].direction

		lw	$a0, ($s4)				# $v0 = get_valid_directions(
		lw	$a1, ($s5)				# 		&ghosts[ghost_id].x
		la	$a2, valid_directions			#		&ghosts[ghost_id].y
		jal	get_valid_directions			# 		valid_direction)

		move	$s3, $v0				# int n_valid_dirs = $v0
		
		check_n_valid_dirs_eq_0:
			beqz	$s3, ghost_id_lt_NUM_GHOSTS__loop_step	# if (n_vaild_dirs == 0) {continue}
		
		check_whether_ghost_reached_decision_point:
			bgt	$s3, 2, generate_new_direction			# if (n_valid_dirs > 2 ||
										#
			move	$a0, $s4					#	!try_move(
			move	$a1, $s5					#		&ghosts[ghost_id].x
			lw	$a2, ($s6)					#		&ghosts[ghost_id].y
			jal	try_move					#		ghosts[ghost_id].direction)
										#  )
			beq	$v0, 1, ghost_id_lt_NUM_GHOSTS__loop_step	# 

			generate_new_direction:
				jal	random_number			# $t0 = random_number()
				move	$t0, $v0

				remu	$t1, $t0, $s3			# uint32_t dir_index = $t0 % n_valid_dirs

				mul	$t2, $t1, SIZEOF_INT		# ghosts[ghost_id].direction = valid_directions[dir_index]	
				lw	$t3, valid_directions($t2)	
				sw	$t3, ($s6) 			

					
				move	$a0, $s4			# try_move(	
				move	$a1, $s5			#	&ghosts[ghost_id].x
				move	$a2, $t3			#	&ghosts[ghost_id].y
				jal	try_move			#	ghosts[ghost_id].direction

	ghost_id_lt_NUM_GHOSTS__loop_step:
		addi	$s0, $s0, 1				# ghost_id++
		b	ghost_id_lt_NUM_GHOSTS__loop_cond

	ghost_id_lt_NUM_GHOSTS__loop_end:

do_ghost_logic__epilogue:
	pop	$s6
	pop	$s5
	pop	$s4
	pop	$s3
	pop	$s2
	pop	$s1
	pop	$s0
	pop	$ra
	end
	jr	$ra


################################################################################
################################################################################
###                   PROVIDED FUNCTIONS — DO NOT CHANGE                     ###
################################################################################
################################################################################

	.data
get_seed_prompt_msg:
	.asciiz "Enter a non-zero number for the seed: "
invalid_seed_msg:
	.asciiz "Seed can't be zero.\n"

################################################################################
# .TEXT <get_seed>
	.text
get_seed:
	# Args:     void
	#
	# Returns:  void
	#
	# Frame:    [$ra]
	# Uses:     [$v0, $a0]
	# Clobbers: [$v0, $a0]
	#
	# Locals:
	#   - $v0: copy of lfsr_state
	#
	# Structure:
	#   get_seed
	#   -> [prologue]
	#       -> body
	#       -> loop_start
	#       -> loop_end
	#   -> [epilogue]
	#
	# PROVIDED FUNCTION — DO NOT CHANGE

get_seed__prologue:
	begin
	push	$ra

get_seed__body:
get_seed__loop:					# while (TRUE) {
	li	$v0, 4				#   syscall 4: print_string
	la	$a0, get_seed_prompt_msg
	syscall					#   printf("Enter a non-zero number for the seed: ");

	li	$v0, 5				#   syscall 5: read_int
	syscall
	sw	$v0, lfsr_state			#   scanf("%u", &lfsr_state);

	bnez	$v0, get_seed__loop_end		#   if (lfsr_state != 0) break;

	li	$v0, 4				#   syscall 4: print_string
	la	$a0, invalid_seed_msg
	syscall					#   printf("Seed can't be zero.\n");

	b	get_seed__loop			# }

get_seed__loop_end:
get_seed__epilogue:
	pop	$ra
	end

	jr	$ra


################################################################################
# .TEXT <random_number>
	.text
random_number:
	# Args:     void
	#
	# Returns:
	#    - $v0: uint32_t
	#
	# Frame:    [$ra]
	# Uses:     [$t0, $t1, $t2, $v0]
	# Clobbers: [$t0, $t1, $t2, $v0]
	#
	# Locals:
	#   - $t0: uint32_t bit
	#   - $t1: copy of lfsr_state
	#   - $t2: temporary shift result
	#
	# Structure:
	#   random_number
	#   -> [prologue]
	#       -> body
	#   -> [epilogue]
	#
	# PROVIDED FUNCTION — DO NOT CHANGE

random_number__prologue:
	begin
	push	$ra

random_number__body:
	lw	$t1, lfsr_state		# load lfsr_state
	move	$t0, $t1		# uint32_t bit = lfsr_state;

	srl	$t2, $t1, 10		# lfsr_state >> 10
	xor	$t0, $t0, $t2		# bit ^= lfsr_state >> 10;

	srl	$t2, $t1, 30		# lfsr_state >> 30
	xor	$t0, $t0, $t2		# bit ^= lfsr_state >> 30;

	srl	$t2, $t1, 31		# lfsr_state >> 31
	xor	$t0, $t0, $t2		# bit ^= lfsr_state >> 31;

	andi	$t0, $t0, 1		# bit &= 0x1u;

	sll	$t1, $t1, 1		# lfsr_state <<= 1;
	or	$t1, $t1, $t0		# lfsr_state |= bit;

	sw	$t1, lfsr_state		# store lfsr_state
	move	$v0, $t1		# return lfsr_state;

random_number__epilogue:
	pop	$ra
	end

	jr	$ra
