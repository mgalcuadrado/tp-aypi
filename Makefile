CFLAGS = -c -Wall -pedantic -std=c99 -c
CC = gcc
LFLAGS = -lSDL2 -lm

all: hangon

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) pixel.c

imagen.o: imagen.c imagen.h config.h pixel.h
	$(CC) $(CFLAGS) imagen.c

paleta.o: paleta.c paleta.h pixel.h
	$(CC) $(CFLAGS) paleta.c

textos.o: textos.c textos.h config.h
	$(CC) $(CFLAGS) textos.c

ruta.o : ruta.c ruta.h imagen.h figuras.h
	$(CC) $(CFLAGS) ruta.c

fondo.o: fondo.c fondo.h 
	$(CC) $(CFLAGS) fondo.c

config.o: config.c config.h
	$(CC) $(CFLAGS) config.c

figuras.o: figuras.c figuras.h config.h imagen.h
	$(CC) $(CFLAGS) figuras.c

roms.o: roms.c roms.h figuras.h imagen.h
	$(CC) $(CFLAGS) roms.c

main.o: main.c config.h imagen.h pixel.h fondo.h paleta.h roms.h figuras.h moto.h ruta.h textos.h
	$(CC) $(CFLAGS) main.c $(LFLAGS)

moto.o: moto.c moto.h imagen.h paleta.h
	$(CC) $(CFLAGS) moto.c

hangon: textos.o pixel.o imagen.o config.o paleta.o ruta.o fondo.o roms.o figuras.o moto.o main.o 
	$(CC) textos.o pixel.o imagen.o config.o paleta.o ruta.o fondo.o roms.o figuras.o moto.o main.o -o hangon  $(LFLAGS)

clear:
	rm *.o hangon
