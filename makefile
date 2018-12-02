code: code.o lecture.o miseenpage.o
	gcc code.o lecture.o miseenpage.o -o code -lm

code.o: code.c lecture.h miseenpage.h
	gcc -c code.c -lm

lecture.o: lecture.c lecture.h
	gcc -c lecture.c

miseenpage.o: miseenpage.c miseenpage.h
	gcc -c miseenpage.c