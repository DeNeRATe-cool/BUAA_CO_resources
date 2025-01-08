# int catalanArray[20] = {1, 1}; 
# int n;
# scanf("%d", &n);
# for(int i = 2; i <= n; i++) {
# 	for(int j = 0; j < i; j++) {
# 		catalanArray[i] += catalanArray[j] * catalanArray[i - j - 1];
# 		printf("%d\n", catalanArray[i]);
# 	}
# }
# printf("catalan[%d]=%d\n", n, catalanArray[n]);

.data
	array: .space 1000
	outputPrompt_1: .asciiz "catalan["
	outputPrompt_2: .asciiz "]="
	newLine: .asciiz "\n"

.text
	main:
		# set initial value of location 0/1
		li $t0, 1
		li $t1, 0
		sw $t0, array($t1)
		addi $t1, $t1, 4
		sw $t0, array($t1)
	
		# start process
		li $v0, 5
		syscall
		move $s0, $v0	# $s0: n
		
		li $t0, 2	# $t0: i
		FOR_i:
			bgt $t0, $s0, END_FOR_i

			sll $t2, $t0, 2
									
			li $t1, 0	# $t1: j
			FOR_j:
				beq $t1, $t0, END_FOR_j
				
				sll $t3, $t1, 2	# j
				sub $t4, $t2, $t3
				subi $t4, $t4, 4	# i - j - 1
				
				lw $t3, array($t3)
				lw $t4, array($t4)
				mult $t3, $t4
				mflo $t3
				lw $t5, array($t2)
				add $t5, $t5, $t3
				sw $t5, array($t2)
				
				# print partly
				li $v0, 1
				lw $a0, array($t2)
				syscall
				li $v0, 4
				la $a0, newLine
				syscall
				
				addi $t1, $t1, 1
				j FOR_j
		END_FOR_j:
		
			addi $t0, $t0, 1
			j FOR_i
	END_FOR_i:
		
	li $v0, 4
	la $a0, outputPrompt_1
	syscall
	li $v0, 1
	move $a0, $s0
	syscall
	li $v0, 4
	la $a0, outputPrompt_2
	syscall
	sll $t0, $s0, 2
	lw $a0, array($t0)
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall