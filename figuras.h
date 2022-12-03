#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdbool.h>
#include "imagen.h"


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
    BELL, 
    FORUM,
    DELFIN,
    SEMAFORO,
    BANNER_LARGADA,
    VIGA_BANNER
} figs_t;

size_t figura_get_inicio (figs_t fig);
size_t figura_get_ancho (figs_t fig);
size_t figura_get_alto (figs_t fig);


#endif

