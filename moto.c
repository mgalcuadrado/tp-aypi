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
    bool acelera, frena, mover_izq, mover_der;
  //  size_t n_textos[CANTIDAD_TEXTOS];
};
//
typedef struct{ //Se define aca porque es una estructura solo para el tda
    size_t x,y;
}stmoto_pos_t;

static const stmoto_pos_t pos[4] = {
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
    m->acelera = ac_i;
    m->frena = fr_i;
    m->mover_izq = izq_i;
    m->mover_der = der_i;
  /*  m->n_textos[TOP] = 1000000;
    m->n_textos[TIME] = TIEMPO_JUEGO;
    m->n_textos[SCORE] = 0;
    m->n_textos[STAGE] = 1;
    m->n_textos[SPEED] = 0;
    */
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

bool moto_esta_acelerando (moto_t * m){
    return m->acelera;
}

bool moto_esta_frenando (moto_t * m){
    return m->frena;
}

bool moto_gira_der (moto_t * m){
    return m->mover_der;
}

bool moto_gira_izq (moto_t * m){
    return m->mover_izq;
}

void moto_set_pos(moto_t * m, short p){
    m->pos = p;
}

void moto_set_x (moto_t * m, size_t x, size_t tiempo){
    if(tiempo > 0 || m->x <= META_MOTO)
        m->x = x;
}

void moto_set_vel (moto_t * m, size_t v){
    m->vel = v;
}

void moto_set_acelerar (moto_t * m, bool ac){
    m->acelera = ac;
}

void moto_set_frenar (moto_t * m, bool fr){
    m->frena = fr;
}

void moto_set_der (moto_t * m, bool d){
    m->mover_der = d;
}

void moto_set_izq (moto_t * m, bool i){
    m->mover_izq = i;
}

bool moto_pegar(imagen_t **imagen, imagen_t *origen[], moto_t *moto, size_t t, bool choque){
    if (moto->pos < 0){
        imagen_t *reflejo = imagen_reflejar(origen[-1 * (moto->pos)]);
        if (reflejo == NULL) {
            return false;
        }
        imagen_pegar_con_paleta(*imagen, reflejo, pos[-1 * moto->pos].x, pos[-1 * moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frena) * 2)]);
        imagen_destruir(reflejo);
    }
    else{
        imagen_pegar_con_paleta(*imagen, origen[moto->pos], pos[moto->pos].x, pos[moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frena) * 2)]);
    }
    return true;
}

