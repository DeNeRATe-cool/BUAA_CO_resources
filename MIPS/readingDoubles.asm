.data
	message: .asciiz "Enter the value of e: "
	zero: .double 0.0
	
.text
	main:
		ldc1 $f4, zero
	
		li $v0, 4
		la $a0, message
		syscall
		
		# Get the double from the user
		li $v0, 7
		syscall
		
		# Display user's input
		li $v0, 3
		add.d $f12, $f0, $f4
		syscall