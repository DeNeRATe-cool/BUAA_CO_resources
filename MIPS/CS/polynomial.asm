.data

.text
	main:
		li $v0, 5
		syscall
		move $s0, $v0	# $s0: n
		
		li $v0, 5
		syscall
		move $s1, $v0	# $s1: x
		
		li $s2, 1	# $s2: step
		li $s3, 0	# $s3: answer
		li $s4, 101	# $s4: mod
		
		div $s1, $s4
		mfhi $s1
		
		li $t0, 0	# $t0: i
		FOR_1:
			bgt $t0, $s0, END_FOR_1
			
			li $v0, 5
			syscall
			move $t1, $v0	# $t1: a_i
			
			div $t1, $s4
			mfhi $t1
			
			mult $t1, $s2
			mflo $t1
			div $t1, $s4
			mfhi $t1
			
			add $s3, $s3, $t1
			div $s3, $s4
			mfhi $s3
			
			mult $s1, $s2
			mflo $s2
			div $s2, $s4
			mfhi $s2
			
			addi $t0, $t0, 1
			j FOR_1
	END_FOR_1:
		li $v0, 1
		move $a0, $s3
		syscall
	
	li $v0, 10
	syscall