#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>

#define CANTIDAD_TESELAS 4096
#define CANTIDAD_FIGURAS 13
#define CANTIDAD_RUTAS 4
#define CANTIDAD_ROMS 18

#define ANCHO_TESELA 8
#define ALTO_TESELA 8
#define ANCHO_RUTA 512
#define ALTO_RUTA_OG 128
#define ALTO_RUTA_NUEVO 96

/*#define VENTANA_ANCHO 800
#define VENTANA_ALTO 600*/
#define VENTANA_ANCHO 320
#define VENTANA_ALTO 224

#define FILA_CUADROS 3
#define COLUMNA_CUADRO_TOP 5
#define COLUMNA_CUADRO_SCORE 7
#define COLUMNA_CUADRO_TIME 6
#define FILA_GOAL_GAMEOVER 2
#define COLUMNA_GAMEOVER 15
#define COLUMNA_GOAL 7

#define CANTIDAD_TEXTOS 6

#define JUEGO_FPS 30

/*
#define ARCHIVO_ROM_R   "roms/6841.rom"
#define ARCHIVO_ROM_G   "roms/6842.rom"
#define ARCHIVO_ROM_B   "roms/6843.rom"
#define ARCHIVO_ROM_RUTA "roms/6840.rom"
#define ARCHIVO_ROM_FIGURA_1 "roms/6819.rom"
#define ARCHIVO_ROM_FIGURA_2 "roms/6820.rom"
#define ARCHIVO_ROM_FIGURA_3 "roms/6821.rom"
#define ARCHIVO_ROM_FIGURA_4 "roms/6822.rom"
#define ARCHIVO_ROM_FIGURA_5 "roms/6823.rom"
#define ARCHIVO_ROM_FIGURA_6 "roms/6824.rom"
#define ARCHIVO_ROM_FIGURA_7 "roms/6825.rom"
#define ARCHIVO_ROM_FIGURA_8 "roms/6826.rom"
#define ARCHIVO_ROM_FIGURA_9 "roms/6827.rom"
#define ARCHIVO_ROM_FIGURA_10 "roms/6828.rom"
#define ARCHIVO_ROM_FIGURA_11 "roms/6829.rom"
#define ARCHIVO_ROM_FIGURA_12 "roms/6830.rom"
#define ARCHIVO_ROM_FIGURA_13 "roms/6845.rom"
#define ARCHIVO_ROM_FIGURA_14 "roms/6846.rom"

*/

extern const uint16_t mosaico_cuadro_top[FILA_CUADROS][COLUMNA_CUADRO_TOP];
extern const uint8_t mosaico_paleta_top[FILA_CUADROS][COLUMNA_CUADRO_TOP];
extern const uint16_t mosaico_cuadro_score[FILA_CUADROS][COLUMNA_CUADRO_SCORE];
extern const uint8_t mosaico_paleta_score[FILA_CUADROS][COLUMNA_CUADRO_SCORE];
extern const uint16_t mosaico_cuadro_time[FILA_CUADROS][COLUMNA_CUADRO_TIME];
extern const uint8_t mosaico_paleta_time[FILA_CUADROS][COLUMNA_CUADRO_TIME];
extern const uint16_t mosaico_cuadro_goal[FILA_GOAL_GAMEOVER][COLUMNA_GOAL];
extern const uint8_t mosaico_paleta_goal[FILA_GOAL_GAMEOVER][COLUMNA_GOAL];
extern const uint16_t mosaico_cuadro_gameover[FILA_GOAL_GAMEOVER][COLUMNA_GAMEOVER];
extern const uint8_t mosaico_paleta_gameover[FILA_GOAL_GAMEOVER][COLUMNA_GAMEOVER];
//Perdon mechi xD
/*

typedef enum{
    ARCHIVO_ROM_B,
    ARCHIVO_ROM_G,
    ARCHIVO_ROM_R,
    ARCHIVO_ROM_RUTA,
    ARCHIVO_ROM_FIGURA_1,
    ARCHIVO_ROM_FIGURA_2,
    ARCHIVO_ROM_FIGURA_3,
    ARCHIVO_ROM_FIGURA_4,
    ARCHIVO_ROM_FIGURA_5,
    ARCHIVO_ROM_FIGURA_6,
    ARCHIVO_ROM_FIGURA_7,
    ARCHIVO_ROM_FIGURA_8,
    ARCHIVO_ROM_FIGURA_9,
    ARCHIVO_ROM_FIGURA_10,
    ARCHIVO_ROM_FIGURA_11,
    ARCHIVO_ROM_FIGURA_12,
    ARCHIVO_ROM_FIGURA_13,
    ARCHIVO_ROM_FIGURA_14,
}archivos_t;

const char *archivos_rom[CANTIDAD_ROMS] = {  
[ARCHIVO_ROM_R] = "roms/6841.rom",
[ARCHIVO_ROM_G] = "roms/6842.rom",
[ARCHIVO_ROM_B] = "roms/6843.rom",
[ARCHIVO_ROM_RUTA] = "roms/6840.rom",
[ARCHIVO_ROM_FIGURA_1] = "roms/6819.rom",
[ARCHIVO_ROM_FIGURA_2] = "roms/6820.rom",
[ARCHIVO_ROM_FIGURA_3] = "roms/6821.rom",
[ARCHIVO_ROM_FIGURA_4] = "roms/6822.rom",
[ARCHIVO_ROM_FIGURA_5] = "roms/6823.rom",
[ARCHIVO_ROM_FIGURA_6] = "roms/6824.rom",
[ARCHIVO_ROM_FIGURA_7] = "roms/6825.rom",
[ARCHIVO_ROM_FIGURA_8] = "roms/6826.rom",
[ARCHIVO_ROM_FIGURA_9] = "roms/6827.rom",
[ARCHIVO_ROM_FIGURA_10] = "roms/6828.rom",
[ARCHIVO_ROM_FIGURA_11] = "roms/6829.rom",
[ARCHIVO_ROM_FIGURA_12] = "roms/6830.rom",
[ARCHIVO_ROM_FIGURA_13] = "roms/6845.rom",
[ARCHIVO_ROM_FIGURA_14] = "roms/6846.rom",
};
*/
#endif
