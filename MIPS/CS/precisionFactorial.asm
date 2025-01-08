.data
	fac: .space 800
	carry: .space 800
	newLine: .asciiz "\n"

.text
	main:
			li $s0, 1	# bit of digit
			li $s1, 1	# mult number
			li $s3, 1000000	# modulo number
			sw $s1, fac($zero)
			
			# input n
			li $v0, 5
			syscall
			addi $s2, $v0, 1	# $s2: end of mult number n + 1
			
			# for i in [1, n)
			li $t0, 1
			FOR_1:
				
				beq $t0, $s2, END_FOR_1
				
				# clear 0 for k in [0, $s0)
				li $t1, 0
				FOR_2:
				
					beq $t1, $s0 END_FOR_2
					
					sll $t2, $t1, 2
					sw $zero, carry($t2)
					
					addi $t1, $t1, 1
					j FOR_2
					
			END_FOR_2:
				# calculate for j in [0, $s0)
				li $t1, 0
				FOR_3:
				
					beq $t1, $s0, END_FOR_3
					
					sll $t2, $t1, 2	# $t2 = j
					addi $t3, $t1, 1
					sll $t3, $t3, 2	# $t3 = j + 1
					
					# fac[j] = fac[j] * i + carry[j]
					lw $t4, fac($t2)
					mult $t4, $t0
					mflo $t4
					lw $t5, carry($t2)
					add $t4, $t4, $t5
					sw $t4, fac($t2)
					
					bgt $s3, $t4, GOTO_1
					
					# fac[j] >= 1000000 $s3
					div $t4, $s3
					mflo $t7
					sw $t7, carry($t3)
					mfhi $t7
					sw $t7, fac($t2)
					
					GOTO_1:
					# compare carry[digit] with 0
					sll $t5, $s0, 2
					lw $t4, carry($t5)
					bgtz $t4, GOTO_2
					j GOTO_3
					
					# digit = digit + 1
					GOTO_2:
						addi $s0, $s0, 1
						
					GOTO_3:
						addi $t1, $t1, 1
						j FOR_3
				
			END_FOR_3:
				addi $t0, $t0, 1
				j FOR_1
					
		END_FOR_1:
			
			# output the number
			
			addi $t0, $s0, -1
			sll $t0, $t0, 2
			lw $a0, fac($t0)
			li $v0, 1
			syscall
			
			addi $t0, $s0, -2
			FOR_4:
				beq $t0, -1, END_FOR_4
				
				sll $t1, $t0, 2	# $t1: i
				
				lw $t2, fac($t1)
				li $t5, 1
				li $t3, 0	# count of 1s
				while:
					div	$t4, $t2, $t5
					beqz $t4, exit
					addi $t3, $t3, 1
					
					li $t4, 10
					mult $t4, $t5
					mflo $t5
					
					j while
			exit:
			
				sub $t3, $zero, $t3
				addi $t3, $t3, 6
				
				
				# output the needed 0s
				li $t5, 0
				FOR_5:
					beq $t5, $t3, END_FOR_5
					
					li $v0, 1
					li $a0, 0
					syscall
				
					addi $t5, $t5, 1
					j FOR_5
					
			END_FOR_5:
				
				beqz $t2, GOTO_4
				lw $a0, fac($t1)
				li $v0, 1
				syscall
				
				GOTO_4:
				addi $t0, $t0, -1
				j FOR_4
				
				
		END_FOR_4:
	
	li $v0, 10
	syscall
