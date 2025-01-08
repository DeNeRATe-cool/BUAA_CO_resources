.data
	promptShow: .asciiz "Enter two numbers: \n"
	resultShow: .asciiz "The gcd of two numbers is: "

.text
	main:
		# li $v0, 4
		# la $a0, promptShow
		# syscall
	
		li $v0, 5 # integer 1
		syscall
		move $t0, $v0
		
		li $v0, 5 # integer 2
		syscall
		move $t1, $v0
	
		# return (!b) ? a : gcd(b, a % b);
		# while(b != 0) {
		#	int temp = a;
		#	a = b;
		#	b = temp % b;
		# }
	
		while:	
			beq $t1, $zero, exit
			
			move $t2, $t0
			move $t0, $t1
			div $t2, $t1
			mfhi $t1
			
			j while
		exit:
		
		# li $v0, 4
		# la $a0, resultShow
		# syscall
		
		li $v0, 1
		move $a0, $t0
		syscall
	
	li $v0, 10
	syscall
