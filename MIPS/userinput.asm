.data
	prompt: .asciiz "Enter your age: "
	message: .asciiz "Your age is: "

.text
	# prompt the user to enter age
	li $v0, 4
	la $a0, prompt
	syscall
	
	# get user's input
	li $v0, 5
	syscall
	
	# store the result in $t0
	move $t0, $v0
	
	# print
	li $v0, 4
	la $a0, message
	syscall

	li $v0, 1
	move $a0, $t0
	syscall
	