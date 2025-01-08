.data
	newLine: .asciiz "\n"

.text
	main:
		addi $s0, $zero, 10
		
		jal increaseMyRegister
		
		li $v0, 4
		la $a0, newLine
		syscall
		
		# print value
		li $v0, 1
		move $a0, $s0
		syscall
		
	li $v0, 10
	syscall
	
	increaseMyRegister:
		addi $sp, $sp, -8
		sw $s0, 0($sp)
		sw $ra, 4($sp)
		
		addi $s0, $s0, 30

		# Nested Procedure
		jal printTheValue
		lw $ra, 4($sp)
		
		lw $s0, 0($sp)
		addi $sp, $sp, 8
		
		jr $ra
		
	printTheValue:
		#print new value in function
		li $v0, 1
		move $a0, $s0
		syscall
		
		jr $ra