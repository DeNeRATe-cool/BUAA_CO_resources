.data
array: .space 100
.text
	main:
		la $t1, array
		li $t2, 0
		loop:
			sw $t2, 0($t1)
			addi $t1, $t1, 4
			addi $t2, $t2, 1
			ble $t2, 10, loop
			
		li $v0, 1
		lw $a0, -8($t1)
		syscall
	
