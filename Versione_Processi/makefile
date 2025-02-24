frogger.out: main.o start.o colors.o rana.o coccodrillo.o print.o tane.o proiettile.o score.o menu.o
	gcc main.o start.o tane.o colors.o rana.o coccodrillo.o print.o proiettile.o score.o menu.o -o frogger.out -lncurses -lm -lrt

main.o: funzioni.h main.c preProcessing.h
	gcc -c main.c -o main.o

menu.o: funzioni.h menu.c preProcessing.h
	gcc -c menu.c -o menu.o

score.o: funzioni.h score.c preProcessing.h
	gcc -c score.c -o score.o

proiettile.o: funzioni.h proiettile.c preProcessing.h
	gcc -c proiettile.c -o proiettile.o

coccodrillo.o: funzioni.h coccodrillo.c preProcessing.h
	gcc -c coccodrillo.c -o coccodrillo.o

print.o: funzioni.h print.c preProcessing.h
	gcc -c print.c -o print.o

rana.o: funzioni.h rana.c preProcessing.h
	gcc -c rana.c -o rana.o

colors.o: funzioni.h colors.c preProcessing.h
	gcc -c colors.c -o colors.o

start.o: funzioni.h start.c preProcessing.h
	gcc -c start.c -o start.o

clean:
	rm -f *.o frogger.out
