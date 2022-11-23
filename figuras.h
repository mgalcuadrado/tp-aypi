#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdbool.h>
#include "imagen.h"

/*figuras.o: figuras.c config.h imagen.h
	$(CC) $(CFLAGS) figuras.c*/


typedef struct pos_figuras pos_figuras_t;

// ?????
typedef enum{
    MOTO_1,
    MOTO_2,
    MOTO_3,
    MOTO_4,
    ARBOL,
    CARTEL,
    ROCA,
    CARTEL_BELL, 
    CARTEL_FORUM,
    CARTEL_DELFIN,
    SEMAFORO,
    BANNER_LARGADA,
    VIGA_BANNER
} figs_t;


size_t figura_get_inicio (figs_t fig);
size_t figura_get_ancho (figs_t fig);
size_t figura_get_alto (figs_t fig);


#endif

