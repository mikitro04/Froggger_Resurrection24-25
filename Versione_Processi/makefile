frogger.out: clean main.o start.o
	gcc main.o start.o -o frogger.out -lncurses

main.o: funzioni.h main.c
	gcc -c main.c

start.o: funzioni.h start.c
	gcc -c start.c

clean:
	rm -f *.o