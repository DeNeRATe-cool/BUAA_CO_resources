.data
	message: .asciiz "hi, how are you!"

.text
	main:
		li $s0, 14
		li $s1, 10
		
		bgt $s0, $s1, displayHi
	
	li $v0, 10
	syscall
	
	displayHi:
		li $v0, 4
		la $a0, message
		syscall