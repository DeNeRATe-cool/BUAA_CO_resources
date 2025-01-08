.data
	array: .word 10, 2, 9
	length: .word 3
	sum: .word 0
	average: .word 0

.text
	main:
		la $t0, array # base address
		li $t1, 0 # i = 0
		lw $t2, length # t2 = length
		li $t3, 0 # sum = 0
		
		sumLoop:
			lw $t4, ($t0) # t4 = array[i]
			add $t3, $t3, $t4 # sum = sum + array[i]

			add $t1, $t1, 1 # i = i + 1
			add $t0, $t0, 4 # updating the array address
			blt $t1, $t2, sumLoop # if i < len, then loop again
	
		sw $t3, sum
		
		div $t5, $t3, $t2
		sw $t5, average
		
		li $v0, 1
		lw $a0, average
		syscall
	
	li $v0, 10
	syscall