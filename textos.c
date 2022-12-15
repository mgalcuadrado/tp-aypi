#include "textos.h" 
#include "paleta.h"

#include <string.h>
#include <math.h>

void numeros_a_pantalla(imagen_t *destino, imagen_t **origen, size_t i, int x, int y, size_t *text, size_t paleta){
    char n_string[MAX_CADENA];
    sprintf(n_string,"%ld",text[i]);
    size_t len = strlen(n_string);
    if(i == 1){
        int res = pow(10, (len > 1) ? len - 1 : len);
        size_t aux = text[i]; //La pongo en un auxiliar porque sino modifico el valor *text
        for(size_t j = 0; j < (len > 1 ? len : 2); j++){
            imagen_pegar_con_paleta(destino, origen[0x80 + (2 * (aux/res))], x + (8 * j),y + 16,paleta_3[5]);
            imagen_pegar_con_paleta(destino, origen[0x81 + (2 * (aux/res))], x + (8 * j),y + 24,paleta_3[5]);
            aux -= res * (aux/res);
            res /= 10;
        }  
        return;
    }
    for (size_t j = 0; j < len; j++)
        imagen_pegar_con_paleta(destino, origen[(uint8_t)(n_string[j])], x + (8 * j) + (8 * strlen(textos[i].cadena)) + (i == 4 && text[i] < 100 ? (text[i] < 0 ? 16 : 8) : 0),y,paleta_3[paleta + (i == 3 ? 1 : 0)]);
}

const sttexto_t textos[CANTIDAD_TEXTOS] = {
    [TOP] = {"   ", 0xd, 0x6, 8},
    [TIME] = {" ", 0x89, 0x6, 7},
    [SCORE] = {"      ", 0xbf, 0x6, 7},
    [STAGE] = {"STAGE", 0x14, 0x1c, 5},
    [SPEED] = {"SPEED", 0xc6, 0x1c, 6},
    [KM] = {"KM", 0x10e, 0x1c, 6},
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
