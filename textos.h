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

typedef struct{
    const size_t filas, columnas;
    const void *mosaico;
    const void *paleta;
}stcuadro_t;
 
extern const stcuadro_t cuadro_textos[CANTIDAD_CUADROS];


#endif
