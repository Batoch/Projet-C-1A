code: code.o lecture.o
	gcc code.o lecture.o  -o code -lm -g

code.o: code.c lecture.h
	gcc -c code.c -lm -g

lecture.o: lecture.c lecture.h
	gcc -c lecture.c -g 