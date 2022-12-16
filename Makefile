ftc: ftc.o listfiles.o size.o name.o date.o
	gcc ftc.o listfiles.o size.o name.o -o ftc 

ftc.o: src/ftc.c
	gcc -c -Wall src/ftc.c 

listfiles.o: src/listfiles.c
	gcc -c -Wall src/listfiles.c

name.o : src/name.c
	gcc -c -Wall src/name.c

size.o : src/size.c
	gcc -c -Wall src/size.c

date.o : src/date.c
	gcc -c -Wall src/date.c



