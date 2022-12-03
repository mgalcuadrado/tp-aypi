#include "figuras.h"

#include <stddef.h>


struct pos_figuras{
    size_t inicio, ancho, alto;
};

const pos_figuras_t arr_pos_figuras[CANTIDAD_FIGURAS] = {
    [MOTO_1] = {532, 36, 73},
    [MOTO_2] = {5670, 36, 70},
    [MOTO_3] = {11284, 46, 63},
    [MOTO_4] = {17215, 60, 54},
    [ARBOL] = {50116, 46, 188},
    [CARTEL] = {37390, 96, 112},
    [ROCA] = {69464, 136, 76},
    [BELL] = {82922, 63, 146},
    [FORUM] = {89102, 118, 114},
    [DELFIN] = {119280, 144, 110},
    [SEMAFORO] = {108724, 66, 201},
    [BANNER_LARGADA] = {114518, 244, 48},
    [VIGA_BANNER] = {127098, 198, 48},
};

size_t figura_get_inicio (figs_t fig){
    return arr_pos_figuras[fig].inicio;
}

size_t figura_get_ancho (figs_t fig){
    return arr_pos_figuras[fig].ancho;
}

size_t figura_get_alto (figs_t fig){
    return arr_pos_figuras[fig].alto;
}

