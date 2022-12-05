#ifndef TEXTOS_H
#define TEXTOS_H

#include <stdint.h>
#include "config.h"

typedef enum{
    TOP,
    TIME,
    SCORE,
    STAGE,
    SPEED,
    KM,
    GOAL,
    GAMEOVER,
}texto_t;


typedef struct{
    const char cadena[MAX_CADENA];
    size_t pos_x, pos_y, paleta;
}sttexto_t;


extern const sttexto_t textos[CANTIDAD_TEXTOS];

//Estos son los mosaicos y paletas para generar los mosaicos de los cuadros de textos
extern const uint16_t mos_cuadro_top[FILA_CUADROS][COLUMNA_TOP];
extern const uint8_t mos_paleta_top[FILA_CUADROS][COLUMNA_TOP];

extern const uint16_t mos_cuadro_score[FILA_CUADROS][COLUMNA_SCORE];
extern const uint8_t mos_paleta_score[FILA_CUADROS][COLUMNA_SCORE];

extern const uint16_t mos_cuadro_time[FILA_CUADROS][COLUMNA_TIME];
extern const uint8_t mos_paleta_time[FILA_CUADROS][COLUMNA_TIME];

extern const uint16_t mos_cuadro_goal[FILA_GG][COLUMNA_GOAL];
extern const uint8_t mos_paleta_goal[FILA_GG][COLUMNA_GOAL];

extern const uint16_t mos_cuadro_gameover[FILA_GG][COLUMNA_GAMEOVER];
extern const uint8_t mos_paleta_gameover[FILA_GG][COLUMNA_GAMEOVER];

#endif
