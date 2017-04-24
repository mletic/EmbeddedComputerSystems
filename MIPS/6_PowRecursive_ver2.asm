.data
	poruka: .asciiz "Uneti ceo broj a:\n"
	stepen: .asciiz "Uneti stepen:\n"
.text

main:
	subu $sp, $sp, 24	# Pravimo nas stek frejm
	sw $ra, 20($sp)
	
	la $a0,poruka
	li $v0,4
	syscall
	
	li $v0,5
	syscall
	
	move $a1,$v0 #broj a
	
	la $a0,stepen
	li $v0,4
	syscall
	
	li $v0,5
	syscall
	
	move $a0,$v0 #stepen n
	#add $a0,$a0,1
	
	move $v0,$a1
	move $v1,$a1
	
	jal pow		
	move $a0, $v0	
	li $v0, 1
	syscall

	li $v0, 10		
	syscall
	
pow:	
		subu $sp, $sp, 24	
		sw $ra, 20($sp)		
		sw $a0, 0($sp)		 
		bgt $a0, 1, spusti_stepen	
	
		b powreturn		

spusti_stepen:	
		subi $a0, $a0, 1	
		jal pow			
							
		lw $a0, 0,($sp)		
		mul $v0,$v0,$v1		
powreturn:	
		
		lw $ra, 20($sp)		
		addu $sp, $sp, 24	
		jr $ra	
	
	
	
	