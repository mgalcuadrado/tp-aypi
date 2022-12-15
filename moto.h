#ifndef MOTO_H
#define MOTO_H

#include "imagen.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct moto moto_t;

//Función creada para crear memoria para la estructura moto_t
moto_t * moto_crear (int y_i, short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i, bool choque_i);

//Esta es para destruir la memoria pedida
void moto_destruir(moto_t * m);

//Getter de la intensidad de giro de la moto
short moto_get_pos (moto_t * m);

//Getter del metro de la ruta en el que se encuentra la moto 
size_t moto_get_x (moto_t * m);

//Getter de la velocidad actual la moto
size_t moto_get_vel (moto_t * m);

//Getter de la y actual de la moto
int moto_get_y (moto_t * m);

//Getter de que se apretó el acelerador
bool moto_esta_acelerando (moto_t * m);

//Getter de que se apretó el freno
bool moto_esta_frenando (moto_t * m);

//Getter de que se pulsó el giro hacia la derecha
bool moto_gira_der (moto_t * m);

//Getter de que se pulsó el giro hacia la izquierda
bool moto_gira_izq (moto_t * m);

//Getter de si la moto chocó
bool moto_hay_choque(moto_t * m);

//Setter de la intensidad de giro de la moto 
void moto_set_pos(moto_t * m, short p);

//Setter del metro de la ruta en el que se encuentra la moto
void moto_set_x (moto_t * m, size_t x, size_t tiempo);

//Setter de la velocidad actual la moto
void moto_set_vel (moto_t * m, size_t del, size_t secs, bool mordiendo_banquina);

//Setter de que se soltó el acelerador
void moto_set_acelerar (moto_t * m, bool ac);

//Setter de que se soltó el freno
void moto_set_frenar (moto_t * m, bool fr);

//Setter de que se soltó el giro hacia la derecha
void moto_set_der (moto_t * m, bool d);

//Setter de que se soltó el giro hacia la izquierda
void moto_set_izq (moto_t * m, bool i);

//Setter de la posicion m_y de la moto
void moto_set_y(moto_t *moto, size_t x);   

//Función creada para pegar la moto dependiendo hacia donde está doblando la misma
//recibe una puntero a una imagen, el arreglo de imágenes en el que se encuentran las motos, la moto, el marcador de tiempo y un booleano indicando si hubo o no choques
bool moto_pegar(imagen_t **imagen, imagen_t *origen[], moto_t *moto, size_t t, bool choque);

//esta función verifica si la moto choca con alguna figura, para ello requiere la moto, la distancia en la que está la figura, la posición x de la moto y el ancho de la figura en cuestión
void hay_choque_con_figuras (moto_t * m, size_t ancho, int d, size_t x);

//esta función se encarga de verificar si la moto chocó y, en base a eso, ajustar los parámetros de la moto
//también se encarga de manejar el delay del choque
void manejo_de_choques(moto_t * m, size_t x, size_t *s);

#endif