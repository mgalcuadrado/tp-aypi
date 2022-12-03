#include "moto.h"
#include "paleta.h"
#include <stdlib.h>

//Paleta 0 y 1 para cuando està andando
//Paleta 2 y 3 para cuando està frenando
struct moto{
    short pos;
    size_t x, vel;
    bool acelerar, frenar, mover_izq, mover_der;
};

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

moto_t * moto_crear(short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i){
    moto_t * m = malloc (sizeof(moto_t));
    if (m == NULL) return NULL;
    m->pos = pos_i;
    m->x = x_i;
    m->vel = vel_i;
    m->acelerar = ac_i;
    m->frenar = fr_i;
    m->mover_izq = izq_i;
    m->mover_der = der_i;
    return m;
}

void moto_destruir (moto_t * m){
    free(m);
}

short moto_get_pos (moto_t * m){
    return m->pos;
}

void moto_set_pos(moto_t * m, short p){
    m->pos = p;
}

size_t moto_get_x (moto_t * m){
    return m->x;
}

void moto_set_x (moto_t * m, size_t x){
    m->x = x;
}

size_t moto_get_vel (moto_t * m){
    return m->vel;
}

void moto_set_vel (moto_t * m, size_t v){
    m->vel = v;
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

void pegar_moto(imagen_t *imagen, imagen_t *origen[], moto_t *moto, size_t t){
    if (moto->pos < 0){
        imagen_t *reflejo = imagen_reflejar(origen[-1 * (moto->pos)]);
        imagen_pegar_con_paleta(imagen, reflejo,pos[-1 * moto->pos].x,pos[-1 * moto->pos].y, paleta_4[t % 2 + (moto->frenar) * 2]);
        free(reflejo);
    }
    else
        imagen_pegar_con_paleta(imagen, origen[moto->pos],pos[moto->pos].x,pos[moto->pos].y, paleta_4[t % 2 + (moto->frenar) * 2]);
}