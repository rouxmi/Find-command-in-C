ftc: ftc.o 
	gcc ftc.o -o ftc 

ftc.o: src/ftc.c
	gcc -c -Wall src/ftc.c 


