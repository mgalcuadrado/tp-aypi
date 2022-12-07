#ifndef MOTO_H
#define MOTO_H

#include "imagen.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct moto moto_t;

//Función creada para crear memoria para la estructura moto_t
moto_t * moto_crear(short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i);

//Esta es para destruir la memoria pedida
void moto_destruir(moto_t * m);

//Getter de la intensidad de giro de la moto
short moto_get_pos (moto_t * m);

//Getter del metro de la ruta en el que se encuentra la moto 
size_t moto_get_x (moto_t * m);

//Getter de la velocidad actual la moto
size_t moto_get_vel (moto_t * m);

//Getter de que se apretó el acelerador
bool moto_get_acelerar (moto_t * m);

//Getter de que se apretó el freno
bool moto_get_frenar (moto_t * m);

//Getter de que se pulsó el giro hacia la derecha
bool moto_get_der (moto_t * m);

//Getter de que se pulsó el giro hacia la izquierda
bool moto_get_izq (moto_t * m);

//Getter del tiempo que queda en el juego
size_t moto_get_tiempo(moto_t * m);

//Setter de la intensidad de giro de la moto 
void moto_set_pos(moto_t * m, short p);

//Setter del metro de la ruta en el que se encuentra la moto
void moto_set_x (moto_t * m, size_t x);

//Setter de la velocidad actual la moto
void moto_set_vel (moto_t * m, size_t v);

//Setter de que se soltó el acelerador
void moto_set_acelerar (moto_t * m, bool ac);

//Setter de que se soltó el freno
void moto_set_frenar (moto_t * m, bool fr);

//Setter de que se soltó el giro hacia la derecha
void moto_set_der (moto_t * m, bool d);

//Setter de que se soltó el giro hacia la izquierda
void moto_set_izq (moto_t * m, bool i);

//Función hecha para guardar los puntajes de juego
void moto_set_puntajes(moto_t *moto, size_t x, int y);

//Setter del tiempo jugado, recibe la moto y el valor de tiempo t a asignar
void moto_set_tiempo(moto_t *moto, size_t t);

//Función creada para pegar la moto dependiendo hacia donde está doblando la misma
//recibe una puntero a una imagen, el arreglo de imágenes en el que se encuentran las motos, la moto, el marcador de tiempo y un booleano indicando si hubo o no choques
bool moto_pegar(imagen_t **imagen, imagen_t *origen[], moto_t *moto, size_t t, bool choque);

//Función que imprime los textos en pantalla
//recibe la moto, un puntero a los cuadros, el arreglo de teselas levantadas de la rom y el arreglo de cuadros de textos
void imprimir_textos(moto_t *moto, imagen_t **cuadro, imagen_t * teselas[], imagen_t * cuadros_textos[CANTIDAD_CUADROS]);

#endif