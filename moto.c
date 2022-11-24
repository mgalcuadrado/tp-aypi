#include "moto.h"

//Paleta 0 y 1 para cuando està andando
//Paleta 2 y 3 para cuando està frenando
struct moto{
    short pos;
    size_t x, vel;
    bool acelerar, frenar, mover_izq, mover_der;
};

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
