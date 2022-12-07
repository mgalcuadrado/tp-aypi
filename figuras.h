#ifndef FIGURAS_H
#define FIGURAS_H

#include <stdbool.h>
#include "imagen.h"


typedef struct pos_figuras pos_figuras_t;

// Enumerativo de figuras que aparecen en la pantalla
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

//Getters de las figuras
size_t figura_get_inicio (figs_t fig);
size_t figura_get_ancho (figs_t fig);
size_t figura_get_alto (figs_t fig);

//pegar figura recibe la figura de destino, 
bool pegar_figuras(imagen_t **destino, imagen_t * figuras[], size_t indice, size_t i, size_t *ancho_figura, int dlat, int dcur);

//Pegar semaforo recibe la figura de destino, el arreglo de figuras, la figura de la parte superior del semáforo (que se creó previamente), la posición y donde se pega el semáforo, pos, y el delay de tiempo en ese momento del
//se encarga de pegar el semáforo en la posición que corresponde
bool pegar_semaforo(size_t del, int *pos, imagen_t *figuras[], imagen_t *sup, imagen_t **destino, int y, size_t x);

//Funcion para saber si hay choque con alguna de las figuras
bool hay_choque(size_t ancho_escalado , int d, size_t x, size_t y);

#endif

