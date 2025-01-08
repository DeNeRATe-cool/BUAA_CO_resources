# void solve(int n, char a, char b, char c) {
# 	if(n == 0) return;
# 	solve(n - 1, a, c, b);
# 	printf("%c->%c\n", a, c);
# 	solve(n - 1, b, a, c);
# }
# 
# int main() {
# 	int n;
# 	scanf("%d", &n); 	
# 	
# 	solve(n, 'A', 'B', 'C');
# }

.data
	newLine: .asciiz "\n"
	arrow: .asciiz "->"
	charA: .byte 'A'
	charB: .byte 'B'
	charC: .byte 'C'

.text
	main:
		li $v0, 5
		syscall
		move $s0, $v0	# $s0: n
		
		lb $a1, charA
		lb $a2, charB
		lb $a3, charC
		move $t0, $s0
		
		jal Hanoi
	
	EXIT:
	li $v0, 10
	syscall
	
	Hanoi:
		beq $t0, 0, RETURN
		
		subi $sp, $sp, 4
		sw $t0, 0($sp)
		subi $sp, $sp, 4
		sw $a1, 0($sp)
		subi $sp, $sp, 4
		sw $a2, 0($sp)
		subi $sp, $sp, 4
		sw $a3, 0($sp)
		sub $sp, $sp, 4
		sw $ra, 0($sp)
		
		move $t1, $a2
		move $a2, $a3
		move $a3, $t1
		subi $t0, $t0, 1
		
		jal Hanoi
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		lw $a3, 0($sp)
		addi $sp, $sp, 4
		lw $a2, 0($sp)
		addi $sp, $sp, 4
		lw $a1, 0($sp)
		addi $sp, $sp, 4
		lw $t0, 0($sp)
		addi $sp, $sp, 4
		
		move $a0, $a1
		li $v0, 11
		syscall
		
		la $a0, arrow
		li $v0, 4
		syscall
		
		move $a0, $a3
		li $v0, 11
		syscall
		
		la $a0, newLine
		li $v0, 4
		syscall
		
		subi $sp, $sp, 4
		sw $t0, 0($sp)
		subi $sp, $sp, 4
		sw $a1, 0($sp)
		subi $sp, $sp, 4
		sw $a2, 0($sp)
		subi $sp, $sp, 4
		sw $a3, 0($sp)
		sub $sp, $sp, 4
		sw $ra, 0($sp)
		
		move $t1, $a1
		move $a1, $a2
		move $a2, $t1
		subi $t0, $t0, 1
		
		jal Hanoi
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		lw $a3, 0($sp)
		addi $sp, $sp, 4
		lw $a2, 0($sp)
		addi $sp, $sp, 4
		lw $a1, 0($sp)
		addi $sp, $sp, 4
		lw $t0, 0($sp)
		addi $sp, $sp, 4
		
		RETURN:
		jr $ra
		
