.data
	message: .asciiz "The numbers are equal."
	message1: .asciiz "The numbers are different."
	message2: .asciiz "Nothing happened."
	finish: .asciiz "Finished!"

.text
	main:
		li $t0, 20
		li $t1, 20
		# addi $t0, $zero, 5
		# addi $t1, $zero, 20
		
		beq $t0, $t1, numbersEqual
		li $v0, 4
		la $a0, message1
		syscall
		
	next:
		li $v0, 4
		la $a0, finish
		syscall
		
	li $v0, 10
	syscall
	
	numbersEqual:
		li $v0, 4
		la $a0, message
		syscall
		
		b next