.data
	message: .asciiz "After while loop is done."
	newLine: .asciiz "\n"

.text
	main:
		# i = zero
		addi $t0, $zero, 0
		
		while:
			bgt $t0, 9, exit
			
			jal printInteger
			
			addi $t0, $t0, 1 # i++
			
			j while
		
		exit:
			li $v0, 4
			la $a0, message
			syscall
		
	
	li $v0, 10
	syscall
	
	printInteger:
		li $v0, 1
		add $a0, $zero, $t0
		syscall
		
		li $v0, 4
		la $a0, newLine
		syscall
		
		jr $ra