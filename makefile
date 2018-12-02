code: code.o lecture.o miseenpage.o
	gcc code.o lecture.o miseenpage.o -o code -lm -g

code.o: code.c lecture.h miseenpage.h
	gcc -c code.c -lm -g

lecture.o: lecture.c lecture.h
	gcc -c lecture.c -g 

miseenpage.o: miseenpage.c miseenpage.h lecture.h
	gcc -c miseenpage.c -g