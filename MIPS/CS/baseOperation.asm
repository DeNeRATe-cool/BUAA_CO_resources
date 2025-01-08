.data


.text
	main:
		li $v0, 5
		syscall
		move $t0, $v0
		
		li $v0, 5
		syscall
		move $t1, $v0
		
		li $v0, 5
		syscall
		move $t2, $v0
		
		beq $t2, 0, addOperation
		beq $t2, 1, minusOperation
		beq $t2, 2, multOperation
		b divOperation
		
		EXIT:
		li $v0, 1
		syscall
			
	
	li $v0, 10
	syscall
	
	addOperation:
		add $a0, $t0, $t1
		j EXIT
	
	minusOperation:
		sub $a0, $t0, $t1
		j EXIT
		
	multOperation:
		mult $t0, $t1
		mflo $a0
		j EXIT
	
	divOperation:
		div $t0, $t1
		mflo $a0
		j EXIT