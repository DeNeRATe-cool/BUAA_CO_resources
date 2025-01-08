.data
	str: .space 100

.text
	main:
			li $v0, 5
			syscall
			move $s0, $v0	# $s0: length of string
			
			li $t0, 0
			FOR_1:
				beq $t0, $s0, END_FOR_1
				
				li $v0, 12
				syscall
				sb $v0, str($t0)
				
				addi $t0, $t0, 1
			
			j FOR_1
		END_FOR_1:
			
			li $t0, 0
			FOR_2:
				beq $t0, $s0, GOTO_YES
				
				sub $t1, $s0, $t0
				subi $t1, $t1, 1
				
				lb $t2, str($t0)
				lb $t3, str($t1)
				
				bne $t2, $t3, GOTO_NO
				
				addi $t0, $t0, 1
				j FOR_2
			
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
			
			EXIT:
	
	li $v0, 10
	syscall