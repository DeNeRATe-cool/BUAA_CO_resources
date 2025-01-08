.data

.text
	main:
		li $v0, 5
		syscall
		move $s0, $v0	# $s0: m
		
		beq $s0, 1, GOTO_NO
		
		li $t0, 2
		FOR_1:
			beq $t0, $s0, END_FOR_1	
		
			div $s0, $t0
			mfhi $t1
			beq $t1, 0, GOTO_NO
	
			addi $t0, $t0, 1
			j FOR_1
	
	END_FOR_1:
		j GOTO_YES
		
	
	EXIT:
	li $v0, 10
	syscall
	
	GOTO_YES:
		li $v0, 1
		li $a0, 1
		syscall
		
		j EXIT
		
	GOTO_NO:
		li $v0, 1
		li $a0, 0
		syscall
		
		j EXIT