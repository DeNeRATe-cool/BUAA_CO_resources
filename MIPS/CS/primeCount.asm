# int prime[100];
# int cnt = 0;
# int start = 2, end = 100;
# 
# for(int i = start; i < end;  i++) {
# 	for(int j = 2; j < i; j++) {
# 		if(i % j == 0) break; // j outer_loop
# 	}
# 	prime[cnt] = i;
# 	cnt++;
# }
.data
	primeArray: .space 40
	inputPrompt: .asciiz "please input the range: \n"
	newLine: .asciiz "\n"

.text
	# [start, end)
	# $t0, start
	# $t1, end
	# $t2, addressStep
	# $t5, count
	# $t3, divisor
	# $t4, remainder
main:
		li $v0, 4
		la $a0, inputPrompt
		syscall
		
		li $v0, 5
		syscall
		move $t0, $v0
		
		li $v0, 5
		syscall
		move $t1, $v0
		
		li $t2, 0
		li $t5, 0
		
		Loop_1:
		
			beq $t0, $t1, Done_1
			
			li $t3, 2
		
			Loop_2:
				beq $t3, $t0, addPrime
			
				div $t0, $t3
				mfhi $t4
				beqz $t4, Done_2
		
				addi $t3, $t3, 1
				j Loop_2
				
		addPrime:
			
			sw $t0, primeArray($t2)
			addi $t2, $t2, 4
			addi $t5, $t5, 1
			
		Done_2:
			 addi $t0, $t0, 1
			 j Loop_1
		
	Done_1:
		li $t6, 0
		outputLoop:
			beq $t6, $t2, doneOutput
			
			li $v0, 1
			lw $a0, primeArray($t6)
			syscall
			
			li $v0, 4
			la $a0, newLine
			syscall
			
			addi $t6, $t6, 4
			
			j outputLoop
						
	doneOutput:
		
	
li $v0, 10
syscall
