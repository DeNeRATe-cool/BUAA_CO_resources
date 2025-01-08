.data


.text
	main:
		li $s0, 0 # $s0: cnt
		
		li $v0, 5
		syscall
		move $s1, $v0 # $s1: n
		
		li $t0, 2 # $t0: i
		FOR_i:
			bgt $t0, $s1, END_FOR_i
		
			div $s1, $t0
			mfhi $t1
			bnez $t1, GOTO_1
		
			li $t6, 1 # $t6: flag
			li $t1, 2 # $t1: j
			FOR_j:
				mult $t1, $t1
				mflo $t2
				bgt $t2, $t0, END_FOR_j
				
				div $t0, $t1
				mfhi $t2
				bnez $t2, GOTO_2
			
				li $t6, 0
				j END_FOR_j
			
				GOTO_2:
				addi $t1, $t1, 1
				j FOR_j
		END_FOR_j:
			
			bne $t6, 1, GOTO_1
			WHILE:
				div $s1, $t0
				mfhi $t3
				bnez $t3, EXIT
				
				div $s1, $t0
				mflo $s1
				
				j WHILE
			EXIT:
				addi $s0, $s0, 1
			
			GOTO_1:
			addi $t0, $t0, 1
			j FOR_i
	END_FOR_i:
		
		li $v0, 1
		move $a0, $s0
		syscall
	
	li $v0, 10
	syscall