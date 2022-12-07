#ifndef CONFIG_H
#define CONFIG_H

#include <stdint.h>
#include <stddef.h>

#define MAX_CADENA 15

#define CANTIDAD_TESELAS 4096
#define CANTIDAD_FIGURAS 13
#define CANTIDAD_RUTAS 4
#define CANTIDAD_ROMS 18
#define CANTIDAD_MOTOS 4

#define ANCHO_TESELA 8
#define ALTO_TESELA 8
#define ANCHO_RUTA 512
#define ALTO_RUTA 128

#define VENTANA_ANCHO 320
#define VENTANA_ALTO 224

#define FILA_CUADROS 3
#define COLUMNA_TOP 5
#define COLUMNA_SCORE 7
#define COLUMNA_TIME 6
#define FILA_GG 2
#define COLUMNA_GAMEOVER 16
#define COLUMNA_GOAL 8

#define CANTIDAD_TEXTOS 6
#define CANTIDAD_CUADROS 8

#define JUEGO_FPS 15

#define INICIO_PALETA_SEMAFORO 41
#define FIN_PALETA_SEMAFORO 44
#define PALETA_START 45
#define PALETA_GOAL 47

//Enumerativo de roms
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

extern const char *archivos_rom[CANTIDAD_ROMS];

#endif
