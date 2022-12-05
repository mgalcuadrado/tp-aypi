#include "figuras.h"
#include "ruta.h"

#include <stddef.h>


struct pos_figuras{
    size_t inicio, ancho, alto;
};

pos_figuras_t arr_pos_figuras[CANTIDAD_FIGURAS] = {
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

bool hay_choque (figs_t fig, size_t ancho_escalado, size_t x, size_t y, int arreglo[]){
    for (size_t i = x; i < x + 5; i++){
        if (ruta[i].indice_figura == 9999) continue;
        //162 + figuras_en_ruta[ruta[x + i].indice_figura].y * ((96 - i)/96.0) + figuras_en_ruta[ruta[x + i].indice_figura].y * (i/5000.0) + d_l + d_c - ancho_figura/2, 224 - i - alto_figura, paleta_4[figuras_en_ruta[ruta[x + i].indice_figura].paleta]);
        if (y > figuras_en_ruta[ruta[i].indice_figura].y * ((96 - i) * (i /5000.0) / 96) + arreglo[i - x] - ancho_escalado/2 && y < figuras_en_ruta[ruta[i].indice_figura].y * ((96 - i) * (i /5000.0) / 96) + arreglo[i - x] - ancho_escalado/ 2)
            return true;
    }
    return false;
}