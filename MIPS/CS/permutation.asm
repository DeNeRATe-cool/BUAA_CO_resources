.data
	array: .space 100
	visited: .space 100
	constant_1: .word 1
	newLine: .asciiz "\n"
	newSpace: .asciiz " "

.text
	main:
		li $v0, 5
		syscall
		move $s0, $v0	# $s0: n
		
		jal Permutation
	
	li $v0, 10
	syscall
	
	Permutation:
	
		# process
		bgt $s0, $a2, GOTO_1	# $a2: dep
		PRINT_ANSWER:
		li $t0, 0
		FOR_1:
			beq $t0, $s0, END_FOR_1
				
			sll $t1, $t0, 2
			li $v0, 1
			lw $a0, array($t1)
			syscall
				
			li $v0, 4
			la $a0, newSpace
			syscall
				
			addi $t0, $t0, 1
			j FOR_1	
	END_FOR_1:
		li $v0, 4
		la $a0, newLine
		syscall
		
		jr $ra
		
		GOTO_1:
		li $t0, 0
		FOR_2:
			beq $t0, $s0, END_FOR_2
			
			sll $t1, $t0, 2	# address i
			addi $t5, $t0, 1	# integer i + 1
			sll $t2, $t5, 2	# address i + 1
			sll $t3, $a2, 2	# address dep
			
			lw $t4, visited($t1)	# integer visited[i]
			bne $t4, $zero, GOTO_2
			
			sw $t5, array($t3)
			lw $t6, constant_1
			sw $t6, visited($t1)
			
			subi $sp, $sp, 4
			sw $ra, 0($sp)
			subi $sp, $sp, 4
			sw $a2, 0($sp)
			subi $sp, $sp, 4
			sw $t0, 0($sp)
			subi $sp, $sp, 4
			sw $t1, 0($sp)
			
			addi $a2, $a2, 1
			
			jal Permutation
			
			lw $t1, 0($sp)
			addi $sp, $sp, 4
			lw $t0, 0($sp)
			addi $sp, $sp, 4
			lw $a2, 0($sp)
			addi $sp, $sp, 4
			lw $ra, 0($sp)
			addi $sp, $sp, 4
			
			sw $zero, visited($t1)
			
			GOTO_2:
			addi $t0, $t0, 1
			j FOR_2
	END_FOR_2:
		
		# return with void
		jr $ra
