#ifndef RUTA_H
#define RUTA_H

#include <stdbool.h>
#include "imagen.h"
#include <stddef.h>

bool leer_ruta (imagen_t * ruta[]);

typedef enum {ARBOL, CARTEL, ROCA, BELL, FORUM, DELFIN} figura_t; //esto va a haber que cambiarlo para que coincida con fig

struct figura_en_ruta {
    figura_t figura;
    size_t paleta;
    int y;
    bool reflejar;
};


struct ruta {
    float radio_curva;
    size_t indice_figura;
};

extern const struct figura_en_ruta figuras_en_ruta[];
extern const struct ruta ruta[4200 + 70];


#endif
