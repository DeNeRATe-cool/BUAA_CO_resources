.macro read(%target)
	li $v0, 5
	syscall
	move %target, $v0
.end_macro

.macro print(%target)
	li $v0, 1
	move $a0, %target
	syscall
.end_macro

.data
	arr: .space 1000
	yes: .asciiz "YE5"
	no: .asciiz "N0"

.text
	main:
		read($s0) # $s0: n
	
		li $v0, 8
		la $a0, arr
		li $a1, 100
		syscall
		
		li $t0, 0
		subi $t1, $s0, 1
		
		li $t5, 1 # flag
		while:
			bge $t0, $t1, exit
			
			lb $t2, arr($t0)
			lb $t3, arr($t1)
			bne $t2, $t3, GOTO_1
			b GOTO_2
			
			GOTO_1:
				li $t5, 0
				j exit
			
			GOTO_2:
			addi $t0, $t0, 1
			subi $t1, $t1, 1
			j while
		exit:
		li $t0, 1
		beq $t0, $t5, goto_yes
		b goto_no
		
		goto_yes:
		li $v0, 4
		la $a0, yes
		syscall
		
		j done
		
		goto_no:
		li $v0, 4
		la $a0, no
		syscall
		
	
	done:
	li $v0, 10
	syscall