# Izracunati stepen nekog broja, pomocu rekurzivne funkcije.
# Zadatak 6
		.data
		
string1:	.asciiz	"Unesite broj koji se stepenuje: \n"
string2:	.asciiz	"Unesite stepen: \n"
string3:	.asciiz "\nRezultat: "
novi_red:	.asciiz	"\n"
		
		.text
main:		
		la $a0, string1			# Ispis stringa 1
		li $v0, 4
		syscall
		
		li $v0, 5			# Ucitavanje broja
		syscall
		move $a1, $v0			# Premestamo stepen u $a1
		
		la $a0, novi_red		# Ispis novog reda
		li $v0, 4
		syscall

		la $a0, string2			# Ispis stringa 2
		li $v0, 4
		syscall
		
		li $v0, 5			# Ucitavanje stepena
		syscall
		move $a0, $v0			# Premestamo stepen u $a0

		li $v0, 0			# Inicializujemo rezultat
		jal stepen
		
		move $a1, $v0			# Dobijamo rezultat u $v0 i cuvamo ga u $a1
		
		la $a0, string3			# Ispis stringa 3
		li $v0, 4
		syscall
						
		move $v0, $a1			# Vracamo rezultat u $v0
										
		move $a0, $v0			# Ispisujem rezultat
		li $v0, 1
		syscall

		li $v0, 10			# Izlaz
		syscall

stepen:	
		subu $sp, $sp, 24		# Minimalna velicina frejma je 24 bajta
		sw $ra, 20($sp)			# Cuvamo povratnu adresu pre rekurzivnog poziva
				
		beq $a0, 0, stepenreturn	# Ako smo dosli do poslednjeg elementa

notzero:	
		subi $a0, $a0, 1		# Nije poslednji element, pa oduzimamo 1		
		jal stepen		
		
		bgt $v0, 0, stepenuj		# Proveravamo da li nam je u $v0 0
		move $v0, $a1			# Ako jeste upisujemo broj koji stepenujemo
		j stepenreturn
stepenuj:					# Ako nije stepenujemo
		mul $v0, $a1, $v0

stepenreturn:	
		lw $ra, 20($sp)			# Obnavljamo povratnu adresu
		addu $sp, $sp, 24		# Unistavamo frejm
		jr $ra				# i vracamo se pozivaocu
