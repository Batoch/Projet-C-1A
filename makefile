code: enregistrement.o code.o
	gcc enregistrement.o code.o -o code -lm
enregistrement.o: enregistrement.h enregistrement.c
	gcc -c enregistrement.c
code.o: code.c enregistrement.h
	gcc -c code.c -lm
lecture.o: lecture.c
	gcc -c lecture.c