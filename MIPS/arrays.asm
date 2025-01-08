.data
	myArray: .word 100:3
	newLine: .asciiz "\n"

.text
	main:
		# while loop
		addi $t0, $zero, 0 # clear $t0
		
		while:
			beq $t0, 12, exit
			
			lw $t6, myArray($t0)
			
			li $v0, 1
			addi $a0, $t6, 0
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall
			
			addi $t0, $t0, 4
			
			j while
		
		exit:
		
	# tell system is end of program
	li $v0, 10
	syscall
		
		