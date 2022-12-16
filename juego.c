#include "juego.h"
#include "textos.h"
#include <stdlib.h>
#include "paleta.h"

struct juego{
 size_t n_textos[CANTIDAD_TEXTOS];
};

juego_t * juego_iniciar_parametros(void){
    juego_t * j = malloc(sizeof(struct juego));
    if (j == NULL) return NULL;
    j->n_textos[TOP] = 1000000;
    j->n_textos[TIME] = TIEMPO_JUEGO;
    j->n_textos[SCORE] = 0;
    j->n_textos[STAGE] = 1;
    j->n_textos[SPEED] = 0;
    return j;
}

void juego_finalizar(juego_t * j){
    free(j);
}

size_t juego_get_tiempo(juego_t * j){
    return j->n_textos[TIME];
}

void juego_set_tiempo(juego_t * juego, moto_t *moto, size_t t){
    if(juego->n_textos[TIME] > 0 || moto_get_x(moto) < META_MOTO)
        juego->n_textos[TIME] = TIEMPO_JUEGO - (t / JUEGO_FPS);
}

void juego_set_speed(juego_t *juego, moto_t * moto){
    juego->n_textos[SPEED] = moto_get_vel(moto);
}

void juego_set_puntajes(juego_t * juego, moto_t *moto, float x){
    if(moto_get_x(moto) >= META_MOTO) return;
    if(moto_get_y(moto) > -215 && moto_get_y(moto) < 215){
        if(moto_get_vel(moto) < 117)
            juego->n_textos[SCORE] += 125 * (moto_get_x(moto) - x); //fórmula dada por el enunciado

        else
            juego->n_textos[SCORE] += (moto_get_x(moto) - x) * (3.13 * moto_get_vel(moto) - 240); //fórmula dada por el enunciado

        if(juego->n_textos[TOP] < juego->n_textos[SCORE])
            juego->n_textos[TOP] = juego->n_textos[SCORE];
    }
    else if (moto_get_vel(moto) > 93){
        moto_set_vel(moto, 0, 0, true);
        juego->n_textos[SPEED] = moto_get_vel(moto);
    }
}

void imprimir_textos(juego_t * juego, imagen_t **cuadro, imagen_t *teselas[], imagen_t * cuadros_textos[CANTIDAD_CUADROS]){
    for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
        if(i < (CANTIDAD_TEXTOS - 1))
            numeros_a_pantalla(*cuadro, teselas, i, 8 + textos[i].pos_x + (i < 3 ? 8 : 0),textos[i].pos_y + (i < 3 ? 0x8 : 0),juego->n_textos,textos[i].paleta);

        for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
            imagen_pegar_con_paleta(*cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[textos[i].paleta]);
    }
    imagen_pegar(*cuadro, cuadros_textos[TOP], textos[TOP].pos_x, textos[TOP].pos_y);
    imagen_pegar(*cuadro, cuadros_textos[TIME], textos[TIME].pos_x, textos[TIME].pos_y);
    imagen_pegar(*cuadro, cuadros_textos[SCORE], textos[SCORE].pos_x, textos[SCORE].pos_y);
}