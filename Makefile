CFLAGS = -c -Wall -pedantic -std=c99 -c
CC = gcc
LFLAGS = -lSDL2 -lm

all: hang.on

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) pixel.c

imagen.o: imagen.c imagen.h config.h pixel.h
	$(CC) $(CFLAGS) imagen.c

paleta.o: paleta.c paleta.h pixel.h
	$(CC) $(CFLAGS) paleta.c

config.o: config.c config.h
	$(CC) $(CFLAGS) config.c

ruta.o : ruta.c ruta.h imagen.h figuras.h
	$(CC) $(CFLAGS) ruta.c

fondo.o: fondo.c fondo.h 
	$(CC) $(CFLAGS) fondo.c

figuras.o: figuras.c figuras.h config.h imagen.h
	$(CC) $(CFLAGS) figuras.c

roms.o: roms.c roms.h figuras.h imagen.h
	$(CC) $(CFLAGS) roms.c

main.o: main.c config.h imagen.h pixel.h fondo.h paleta.h roms.h figuras.h moto.h ruta.h
	$(CC) $(CFLAGS) main.c $(LFLAGS)

moto.c: moto.c moto.h imagen.h paleta.h
	$(CC) $(CFLAGS) moto.c

hang.on:  config.o pixel.o imagen.o paleta.o ruta.o fondo.o roms.o figuras.o moto.o main.o 
	$(CC) config.o pixel.o imagen.o paleta.o ruta.o fondo.o roms.o figuras.o moto.o main.o -o hang.on  $(LFLAGS)

clear:
	rm *.o hang.on
