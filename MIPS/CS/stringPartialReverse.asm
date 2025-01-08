.data
	arr: .space 1024

.text
	main:
		li $v0, 5
		syscall
		move $s0, $v0	# $s0 = length
		
		li $v0, 5
		syscall
		move $s1, $v0	# $s1 = start pointer
		
		li $v0, 5
		syscall
		move $s2, $v0	# $s2 = end pointer
		
		li $v0, 8
		la $a0, arr	# address of string
		li $a1, 1024	# reserve bytes
		syscall
		
		while:
			bgt $s1, $s2, exit
			lb $t1, arr($s1)
			lb $t2, arr($s2)
			sb $t1, arr($s2)
			sb $t2, arr($s1)
			
			addi $s1, $s1, 1
			addi $s2, $s2, -1
			j while
	exit:
		li $v0, 4
		la $a0, arr
		syscall
		
	li $v0, 10
	syscall