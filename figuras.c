#include "config.h"
#include <stddef.h>

struct pos_figuras{
    size_t inicio, ancho, alto;
};

typedef struct pos_figuras pos_figuras_t;

// ?????
typedef enum{
    MOTO_1,
    MOTO_2,
    
} enumfigs_t;

const pos_figuras_t arr_pos_figuras[CANTIDAD_FIGURAS] = {
    [MOTO_1] = {532, 36, 73},
    [MOTO_2] = {11284, 46, 63},
    [MOTO_3] = {},
    [MOTO_4] = {},
    [ARBOL] = {},
    [CARTEL] = {},
    [ROCA] = {},
    [CARTEL_BELL] = {},
    [CARTEL_FORUM] = {},
    [CARTEL_DELFIN] = {},
    [SEMAFORO] = {},
    [BANNER_LARGADA] = {},
    [VIGA_BANNER] = {}, 
};


