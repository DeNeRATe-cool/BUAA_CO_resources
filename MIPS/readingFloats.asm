.data
	message: .asciiz "Enter the value of PI: "
	zeroAsFloat: .float 0.0
.text
	main:
		lwc1 $f4, zeroAsFloat
		
		# display message
		li $v0, 4
		la $a0, message
		syscall
		
		# read input
		li $v0, 6
		syscall

		# display the value
		li $v0, 2
		add.s $f12 $f0, $f4
		syscall