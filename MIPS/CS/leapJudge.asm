# if(x % 400 == 0) GOTO_YES
# else if(x % 100 == 0) GOTO_NO
# else if(x % 4 == 0) GOTO_YES
.data

.text
	main:
		li $t1, 400
		li $t2, 100
		li $t3, 4
	
		li $v0, 5
		syscall
		move $s0, $v0
		
		div $s0, $t1
		mfhi $t0
		beq $t0, 0, GOTO_YES
		div $s0, $t2
		mfhi $t0
		beq $t0, 0, GOTO_NO
		div $s0, $t3
		mfhi $t0
		beq $t0, 0, GOTO_YES
		b GOTO_NO
	
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