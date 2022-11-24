
#include "config.h"


extern const uint16_t mosaico_cuadro_top[FILA_CUADROS][COLUMNA_CUADRO_TOP] = {
    {0x94, 0x95, 0x95, 0x95, 0x96},
    {0x97, 0x98, 0x99, 0x9a, 0x9b},
    {0x9c, 0x9d, 0x9d, 0x9d, 0x9e},
};

extern const uint8_t mosaico_paleta_top[FILA_CUADROS][COLUMNA_CUADRO_TOP] = {
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
};

extern const uint16_t mosaico_cuadro_score[FILA_CUADROS][COLUMNA_CUADRO_SCORE] = {
    {0xb0, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb2},
    {0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9},
    {0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbc},
};

extern const uint8_t mosaico_paleta_score[FILA_CUADROS][COLUMNA_CUADRO_SCORE] = {
    {6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6},
};

extern const uint16_t mosaico_cuadro_time[FILA_CUADROS][COLUMNA_CUADRO_TIME] = {
    {0xa0, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2},
    {0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8},
    {0xa9, 0xaa, 0xaa, 0xaa, 0xaa, 0xab},
};

extern const uint8_t mosaico_paleta_time[FILA_CUADROS][COLUMNA_CUADRO_TIME] = {
    {7,7,7,7,7,7},
    {7,7,7,7,7,7},
    {7,7,7,7,7,7},
};

extern const uint16_t mosaico_cuadro_goal[FILA_GOAL_GAMEOVER][COLUMNA_GOAL] = {
    {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7},
    {0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef},
};

extern const uint8_t mosaico_paleta_goal[FILA_GOAL_GAMEOVER][COLUMNA_GOAL] = {
    {5,5,5,5,5,5,5},
    {5,5,5,5,5,5,5},
};

extern const uint16_t mosaico_cuadro_gameover[FILA_GOAL_GAMEOVER][COLUMNA_GAMEOVER] = {
    {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
    {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f},
};

extern const uint8_t mosaico_paleta_gameover[FILA_GOAL_GAMEOVER][COLUMNA_GAMEOVER] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
};

extern const char *archivos_rom[CANTIDAD_ROMS] = {
    [0] = ARCHIVO_ROM_B,
    [1] = ARCHIVO_ROM_G,
    [2] = ARCHIVO_ROM_R,
    [3] = ARCHIVO_ROM_RUTA,
    [4] = ARCHIVO_ROM_FIGURA_1,
    [5] = ARCHIVO_ROM_FIGURA_2,
    [6] = ARCHIVO_ROM_FIGURA_3,
    [7] = ARCHIVO_ROM_FIGURA_4,
    [8] = ARCHIVO_ROM_FIGURA_5,
    [9] = ARCHIVO_ROM_FIGURA_6,
    [10] = ARCHIVO_ROM_FIGURA_7,
    [11] = ARCHIVO_ROM_FIGURA_8,
    [12] = ARCHIVO_ROM_FIGURA_9,
    [13] = ARCHIVO_ROM_FIGURA_10,
    [14] = ARCHIVO_ROM_FIGURA_11,
    [15] = ARCHIVO_ROM_FIGURA_12,
    [16] = ARCHIVO_ROM_FIGURA_13,
    [17] = ARCHIVO_ROM_FIGURA_14,
};
