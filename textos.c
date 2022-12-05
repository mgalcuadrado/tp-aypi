#include "textos.h"

const stcuadro_t cuadro_textos[CANTIDAD_CUADROS] = {
    [TOP] = {3, 5, mos_cuadro_top[COLUMNA_TOP], mos_paleta_top[COLUMNA_TOP]},
    [SCORE] = {3, 7, mos_cuadro_score[COLUMNA_SCORE], mos_paleta_score[COLUMNA_SCORE]},
    [TIME] = {3, 6, mos_cuadro_time[COLUMNA_TIME], mos_paleta_time[COLUMNA_TIME]},
    [GOAL] = {2, 8, mos_cuadro_goal[COLUMNA_GOAL], mos_paleta_goal[COLUMNA_GOAL]},
    [GAMEOVER] = {2, 16, mos_cuadro_gameover[COLUMNA_GAMEOVER], mos_paleta_gameover[COLUMNA_GAMEOVER]},
};

const uint16_t mos_cuadro_top[FILA_CUADROS][COLUMNA_TOP] = {
    {0x94, 0x95, 0x95, 0x95, 0x96},
    {0x97, 0x98, 0x99, 0x9a, 0x9b},
    {0x9c, 0x9d, 0x9d, 0x9d, 0x9e},
};

const uint8_t mos_paleta_top[FILA_CUADROS][COLUMNA_TOP] = {
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
};

const uint16_t mos_cuadro_score[FILA_CUADROS][COLUMNA_SCORE] = {
    {0xb0, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb2},
    {0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9},
    {0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbc},
};

const uint8_t mos_paleta_score[FILA_CUADROS][COLUMNA_SCORE] = {
    {5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5},
};

const uint16_t mos_cuadro_time[FILA_CUADROS][COLUMNA_TIME] = {
    {0xa0, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2},
    {0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8},
    {0xa9, 0xaa, 0xaa, 0xaa, 0xaa, 0xab},
};

const uint8_t mos_paleta_time[FILA_CUADROS][COLUMNA_TIME] = {
    {5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5},
};

const uint16_t mos_cuadro_goal[FILA_GG][COLUMNA_GOAL] = {
    {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7},
    {0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef},
};

const uint8_t mos_paleta_goal[FILA_GG][COLUMNA_GOAL] = {
    {7, 7, 7, 7, 7, 7, 7, 7},
    {7, 7, 7, 7, 7, 7, 7, 7},
};

const uint16_t mos_cuadro_gameover[FILA_GG][COLUMNA_GAMEOVER] = {
    {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
    {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f},
};

const uint8_t mos_paleta_gameover[FILA_GG][COLUMNA_GAMEOVER] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
