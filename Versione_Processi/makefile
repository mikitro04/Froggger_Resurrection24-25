frogger.out: clean main.o start.o colors.o rana.o coccodrillo.o print.o tane.o proiettile.o score.o menu.o
	gcc main.o start.o tane.o colors.o rana.o coccodrillo.o print.o proiettile.o score.o menu.o -o frogger.out -lncurses -lm -lrt

main.o: funzioni.h main.c
	gcc -c main.c

menu.o: funzioni.h menu.c
	gcc -c menu.c

score.o: funzioni.h score.c
	gcc -c score.c

proiettile.o: funzioni.h proiettile.c
	gcc -c proiettile.c

tane.o: funzioni.h tane.c
	gcc -c tane.c

coccodrillo.o: funzioni.h coccodrillo.c
	gcc -c coccodrillo.c

print.o: funzioni.h print.c
	gcc -c print.c

rana.o: funzioni.h rana.c
	gcc -c rana.c

colors.o: funzioni.h colors.c
	gcc -c colors.c

start.o: funzioni.h start.c
	gcc -c start.c

clean:
	rm -f *.o frogger.out
