CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lncurses -lm -lrt -lSDL2 -lSDL2_mixer

OBJ = main.o start.o tane.o colors.o rana.o coccodrillo.o print.o proiettile.o score.o menu.o

frogger.out: check-deps $(OBJ)
	$(CC) $(OBJ) -o frogger.out $(LDFLAGS)

check-deps:
	@if [ ! -f .deps_checked ]; then \
		echo "Verifica delle dipendenze..."; \
		which sdl2-config > /dev/null || (echo "libsdl2-dev non trovato! Installazione..."; sudo apt-get update && sudo apt-get install -y libsdl2-dev); \
		dpkg -l | grep -q libsdl2-mixer-dev || (echo "libsdl2-mixer-dev non trovato! Installazione..."; sudo apt-get install -y libsdl2-mixer-dev); \
		dpkg -l | grep -q libncurses-dev || (echo "libncurses-dev non trovato! Installazione..."; sudo apt-get install -y libncurses-dev); \
		touch .deps_checked; \
	else \
		echo "Le dipendenze sono già state verificate."; \
	fi

%.o: %.c funzioni.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o frogger.out .deps_checked
