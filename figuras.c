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
} enumfigs_t;

const pos_figuras_t arr_pos_figuras[CANTIDAD_FIGURAS] = {
    [MOTO_1] = {532, 36, 73},
    [MOTO_2] = {5670, 36, 70},
    [MOTO_3] = {11284, 46, 63},
    [MOTO_4] = {17215, 60, 54},
    [ARBOL] = {50116, 46, 188},
    [CARTEL] = {37390, 96, 112},
    [ROCA] = {69464, 136, 76},
    [CARTEL_BELL] = {82922, 63, 146},
    [CARTEL_FORUM] = {89102, 118, 114},
    [CARTEL_DELFIN] = {119280, 144, 110},
    [SEMAFORO] = {108724, 66, 201},
    [BANNER_LARGADA] = {114518, 244, 48},
    [VIGA_BANNER] = {127098, 198, 48},
};


