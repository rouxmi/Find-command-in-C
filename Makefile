ftc: ftc.o listfiles.o size.o name.o util.o date.o mime.o perm.o cat.o error.o link.o
	gcc ftc.o listfiles.o size.o name.o util.o date.o mime.o perm.o cat.o error.o link.o -o ftc 

ftc.o: src/ftc.c
	gcc -c -Wall src/ftc.c 

listfiles.o: src/listfiles.c
	gcc -c -Wall src/listfiles.c

name.o : src/name.c
	gcc -c -Wall src/name.c

size.o : src/size.c
	gcc -c -Wall src/size.c

util.o : src/util.c
	gcc -c -Wall src/util.c

date.o : src/date.c
	gcc -c -Wall src/date.c

mime.o : src/mime.c
	gcc -c -Wall src/mime.c

perm.o : src/perm.c
	gcc -c -Wall src/perm.c

cat.o : src/cat.c
	gcc -c -Wall src/cat.c

error.o : src/error.c
	gcc -c -Wall src/error.c

test.o : src/test.c
	gcc -c -Wall src/test.c

link.o : src/link.c 
	gcc -c -Wall src/link.c

test: test.o listfiles.o size.o name.o util.o date.o mime.o perm.o cat.o error.o link.o
	gcc listfiles.o size.o name.o util.o date.o mime.o perm.o cat.o error.o test.o link.o -o test