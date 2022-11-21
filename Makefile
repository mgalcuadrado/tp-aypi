CFLAGS = -c -Wall -pedantic -std=c99
CC = gcc
LFLAGS = -lSDL2

all: pixeles

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) pixel.c

imagen.o: imagen.c imagen.h config.h pixel.h
	$(CC) $(CFLAGS) imagen.c

paleta.o: paleta.c paleta.h pixel.h
	$(CC) $(CFLAGS) paleta.c

fondo.o: fondo.c fondo.h 
	$(CC) $(CFLAGS) fondo.c

teselas.o: teselas.c teselas.h imagen.h
	$(CC) $(CFLAGS) teselas.c

main.o: main.c imagen.h pixel.h fondo.h paleta.h teselas.h
	$(CC) $(CFLAGS) main.c $(LFLAGS)

pixeles: pixel.o main.o imagen.o paleta.o fondo.o teselas.o
	$(CC) main.o pixel.o imagen.o paleta.o fondo.o teselas.o -o pixeles $(LFLAGS)

clear:
	rm *.o pixeles