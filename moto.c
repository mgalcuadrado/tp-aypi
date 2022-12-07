#include "moto.h"
#include "paleta.h"
#include "textos.h"
#include "config.h"

#include <stdlib.h>

//Paleta 0 y 1 para cuando està andando
//Paleta 2 y 3 para cuando està frenando
struct moto{
    short pos;
    size_t x, vel;
    bool acelerar, frenar, mover_izq, mover_der;
    size_t n_textos[CANTIDAD_TEXTOS];
};
//
typedef struct{ //Se define aca porque es una estructura solo para el tda
    size_t x,y;
}stmoto_pos_t;

const stmoto_pos_t pos[4] = {
    {12,0},     //Posiciones (x,y) de la moto 0
    {12,3},     //Posiciones (x,y) de la moto 1
    {7,10},     //Posiciones (x,y) de la moto 2
    {0,19},     //Posiciones (x,y) de la moto 3
};

//inv de rep: moto_t siempre tiene inicializados sus valores mientras m != NULL

moto_t *moto_crear(short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i){
    moto_t *m = malloc (sizeof(moto_t));
    if (m == NULL) return NULL;
    m->pos = pos_i;
    m->x = x_i;
    m->vel = vel_i;
    m->acelerar = ac_i;
    m->frenar = fr_i;
    m->mover_izq = izq_i;
    m->mover_der = der_i;
    m->n_textos[TOP] = 1000000;
    m->n_textos[TIME] = 75;
    m->n_textos[SCORE] = 0;
    m->n_textos[STAGE] = 1;
    m->n_textos[SPEED] = 0;
    return m;
}

void moto_destruir (moto_t * m){
    free(m);
}

short moto_get_pos (moto_t * m){
    return m->pos;
}

size_t moto_get_x (moto_t * m){
    return m->x;
}

size_t moto_get_vel (moto_t * m){
    return m->vel;
}

bool moto_get_acelerar (moto_t * m){
    return m->acelerar;
}

bool moto_get_frenar (moto_t * m){
    return m->frenar;
}

bool moto_get_der (moto_t * m){
    return m->mover_der;
}

bool moto_get_izq (moto_t * m){
    return m->mover_izq;
}

size_t moto_get_tiempo(moto_t * m){
    return m->n_textos[TIME];
}

void moto_set_pos(moto_t * m, short p){
    m->pos = p;
}

void moto_set_x (moto_t * m, size_t x){
    if(m->n_textos[TIME] > 0 || m->x <= 4150)
        m->x = x;
}

void moto_set_vel (moto_t * m, size_t v){
    m->vel = v;
    m->n_textos[SPEED] = m->vel;
}

void moto_set_acelerar (moto_t * m, bool ac){
    m->acelerar = ac;
}

void moto_set_frenar (moto_t * m, bool fr){
    m->frenar = fr;
}

void moto_set_der (moto_t * m, bool d){
    m->mover_der = d;
}

void moto_set_izq (moto_t * m, bool i){
    m->mover_izq = i;
}

void moto_set_tiempo(moto_t *moto, size_t t){
    if(moto->n_textos[TIME] > 0 || moto->x < 4150)
        moto->n_textos[TIME] = 150 - (t / JUEGO_FPS);
}

void moto_set_puntajes(moto_t *moto, size_t x, int y){
    if(moto->x >= 4150) return;
    if(y > -215 || y < 215){
        if(moto->vel < 117)
            moto->n_textos[SCORE] += 125 * (moto->x - x);

        else
            moto->n_textos[SCORE] += (moto->x - x) * (3.13 * moto->vel - 240);

        if(moto->n_textos[TOP] < moto->n_textos[SCORE])
            moto->n_textos[TOP] = moto->n_textos[SCORE];
    }
    else if (moto->vel > 93){
        moto->vel -= 3;
        moto->n_textos[SPEED] = moto->vel;
    }
}

bool moto_pegar(imagen_t **imagen, imagen_t *origen[], moto_t *moto, size_t t, bool choque){
    if (moto->pos < 0){
        imagen_t *reflejo = imagen_reflejar(origen[-1 * (moto->pos)]);
        if (reflejo == NULL) {
            return false;
        }
        imagen_pegar_con_paleta(*imagen, reflejo, pos[-1 * moto->pos].x, pos[-1 * moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frenar) * 2)]);
        free(reflejo);
    }
    else{
        imagen_pegar_con_paleta(*imagen, origen[moto->pos], pos[moto->pos].x, pos[moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frenar) * 2)]);
    }
    return true;
}

void imprimir_textos(moto_t *moto, imagen_t **cuadro, imagen_t *teselas[], imagen_t * cuadros_textos[CANTIDAD_CUADROS]){
    for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
        if(i < (CANTIDAD_TEXTOS - 1))
            numeros_a_pantalla(*cuadro, teselas, i, 8 + textos[i].pos_x + (i < 3 ? 8 : 0),textos[i].pos_y + (i < 3 ? 0x8 : 0),moto->n_textos,textos[i].paleta);

        for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
            imagen_pegar_con_paleta(*cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[textos[i].paleta]);
    }
    imagen_pegar(*cuadro, cuadros_textos[TOP], textos[TOP].pos_x, textos[TOP].pos_y);
    imagen_pegar(*cuadro, cuadros_textos[TIME], textos[TIME].pos_x, textos[TIME].pos_y);
    imagen_pegar(*cuadro, cuadros_textos[SCORE], textos[SCORE].pos_x, textos[SCORE].pos_y);
}