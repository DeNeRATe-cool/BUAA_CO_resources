.data
	prompMessage: .asciiz "Enter a number to find its factorial: "
	resultMessage: .asciiz "\nThe factorial of the number is "
	number: .word 0
	answer: .word 0

.text
	.globl main
	main:
		# read the number from the user
		li $v0, 4
		la $a0, prompMessage
		syscall
		
		li $v0, 5
		syscall
		
		sw $v0, number
		
		# call the factorial function
		lw $a0, number
		jal findFactorial
		sw $v0, answer
		
		# display the results
		li $v0, 4
		la $a0, resultMessage
		syscall
		
		li $v0, 1
		lw $a0, answer
		syscall
	
	li $v0, 10
	syscall
	
#---------------------------------------
	
	.globl findFactorial
	findFactorial:
		# save the args of last recursion
		subu $sp, $sp, 8
		sw $ra, ($sp)
		sw $s0, 4($sp)
	
		# move the current args to s registers	
		move $s0, $a0
		
		# base case
		li $v0, 1
		beq $a0, 0, factorialDone
		
		# call function
		sub $a0, $a0, 1
		jal findFactorial
		
		# renew the $v0 register
		mul $v0, $a0, $v0
		
		# jump registers
		factorialDone:
			lw $ra, ($sp)
			lw $a0, 4($sp)
			addu $sp, $sp, 8
			jr $ra

		
		
	