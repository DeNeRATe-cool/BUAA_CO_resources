.data
	messageLess: .asciiz "The number is less than the other."
	messageGreater: .asciiz "The number is greater than the other."

.text
	main:
		li $t0, 300
		li $t1, 200
		
		slt $s0, $t0, $t1
		bne $s0, $zero, printMessageLess
		jal printMessageGreater
		
		next:
	
	li $v0, 10
	syscall
	
	printMessageLess:
		li $v0, 4
		la $a0, messageLess
		syscall

		b next
		
	printMessageGreater:
		li $v0, 4
		la $a0, messageGreater
		syscall
		
		jr $ra