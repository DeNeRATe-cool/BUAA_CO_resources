.data
array: .space 1145
.text
main:
	la $s0, array
	li $v0, 5
	syscall
	move $s1, $v0
	li $v0, 5
	syscall
	move $s2, $v0
	li $v0, 5
	syscall
	move $s3, $v0
	add $s2, $s2, $t0
	add $s3, $s3, $t0
	
	li $a1 1140
	la $a0, array
	li $v0, 8
	syscall
	beq $s2, $s3, exit
	loop:
		lb $t2, array($s2)
		lb $t3, array($s3)
		sb $t3, array($s2)
		sb $t2, array($s3)
		addi $s2, $s2, 1
		addi $s3, $s3, -1
		blt $s2, $s3, loop
	exit:
	li $v0, 4
	syscall
	li $v0, 10
	syscall
	
	
