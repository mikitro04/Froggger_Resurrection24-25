frogger.out: clean main.o start.o colors.o rana.o
	gcc main.o start.o colors.o rana.o -o frogger.out -lncurses

main.o: funzioni.h main.c
	gcc -c main.c

print.o: funzioni.h print.c
	gcc -c print.c

rana.o: funzioni.h rana.c
	gcc -c rana.c

colors.o: funzioni.h colors.c
	gcc -c colors.c

start.o: funzioni.h start.c
	gcc -c start.c

clean:
	rm -f *.o