CFLAGS = -c -Wall -pedantic -std=c99
CC = gcc
LFLAGS = -lSDL2

all: pixeles

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) pixel.c
	
config.o: config.c config.h
	$(CC) $(CFLAGS) config.c

imagen.o: imagen.c imagen.h config.h pixel.h
	$(CC) $(CFLAGS) imagen.c

paleta.o: paleta.c paleta.h pixel.h
	$(CC) $(CFLAGS) paleta.c

fondo.o: fondo.c fondo.h 
	$(CC) $(CFLAGS) fondo.c

figuras.o: figuras.c figuras.h config.h imagen.h
	$(CC) $(CFLAGS) figuras.c

teselas.o: teselas.c teselas.h figuras.h imagen.h
	$(CC) $(CFLAGS) teselas.c

main.o: main.c config.h imagen.h pixel.h fondo.h paleta.h teselas.h figuras.h moto.h
	$(CC) $(CFLAGS) main.c $(LFLAGS)

moto.c: moto.c moto.h
	$(CC) $(CFLAGS) moto.c

pixeles: pixel.o imagen.o paleta.o fondo.o config.o teselas.o figuras.o moto.o main.o 
	$(CC) pixel.o imagen.o paleta.o fondo.o config.o teselas.o figuras.o moto.o main.o -o pixeles  $(LFLAGS)

clear:
	rm *.o pixeles
