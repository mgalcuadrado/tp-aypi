#ifndef MOTO_H
#define MOTO_H

#include "imagen.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct moto moto_t;

moto_t * moto_crear(short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i);

void moto_destruir(moto_t * m);

short moto_get_pos (moto_t * m);

void moto_set_pos(moto_t * m, short p);

size_t moto_get_x (moto_t * m);

void moto_set_x (moto_t * m, size_t x);

size_t moto_get_vel (moto_t * m);

void moto_set_vel (moto_t * m, size_t v);

bool moto_get_acelerar (moto_t * m);

bool moto_get_frenar (moto_t * m);

bool moto_get_der (moto_t * m);

bool moto_get_izq (moto_t * m);

void moto_set_acelerar (moto_t * m, bool ac);

void moto_set_frenar (moto_t * m, bool fr);

void moto_set_der (moto_t * m, bool d);

void moto_set_izq (moto_t * m, bool i);

void pegar_moto(imagen_t *imagen, imagen_t *origen[], moto_t *moto, size_t t);

#endif