#zadatak 4
#za uneti n izracunati sumu prvih n neparnih prirodnih brojeva rekurzivnom funkcijom
.text

main:		
		subu $sp, $sp, 24	# Pravimo nas stek frejm
		sw $ra, 20($sp)

		li $v0, 5		#unesemo broj n
		syscall
		
		move $a0, $v0

		jal factorial		# Dobili smo rezultat u $v0,
		move $a0, $v0		# ispisujem rezultat
		li $v0, 1
		syscall

		li $v0, 10			# izlaz
		syscall

		
factorial:	
		subu $sp, $sp, 24	# Minimalna velicina frejma je 24 bajta
		sw $ra, 20($sp)		# Cuvamo povratnu adresu pre rekurzivnog poziva
		sw $a0, 0($sp)		# Cuvamo i nase parametre
							
		bgt $a0, 1, notbasecase	# If arg > 1, nije osnovni slucaj pa preskoci
basecase:	
		li $v0, 1		# Osnovni slucaj: sum(1) je 1. uslov za izlazak iz rekurzije
		b factreturn		# Sada mozemo vratiti rezultat.

notbasecase:	
		subi $a0, $a0, 1	# Nije osnovni slucaj, znaci da treba da udje u rekurziju i da radi
		jal factorial		# parametar i poziv druge funkcije.
					# Sada poziv vraca rezultat u $v0
		lw $a0, 0,($sp)		# Ucitamo ponovo nas originalni parametar sa stek frejma
		
		remu $t3, $a0, 2	#proverava da li je deljiv sa dva
		beq $t3, 1, saberi	#ako nije doda ga na zbir tj na v0
		li $a0, 0		#ako je paran stavi nulu pa doda nulu na rez
		
saberi:
		addu $v0, $a0, $v0	# result = nas parametar + sum(nas parametar - 1)
		

factreturn:	
		lw $ra, 20($sp)		# Obnavljamo povratnu adresu
		addu $sp, $sp, 24	# Unistavamo frejm
		jr $ra			# i vracamo se pozivaocu
