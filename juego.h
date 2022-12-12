#ifndef JUEGO_H
#define JUEGO_H

#include "moto.h"
#include <stddef.h>
#include "config.h"
#include "imagen.h"

typedef struct juego juego_t;

juego_t * juego_iniciar_parametros(void);
void juego_finalizar(juego_t * j);

size_t juego_get_tiempo(juego_t *juego);
void juego_set_tiempo(juego_t *juego, moto_t *moto, size_t t);
void juego_set_speed(juego_t *juego, moto_t * moto);
void juego_set_puntajes(juego_t *juego, moto_t *moto, size_t x, int y);

//Función que imprime los textos en pantalla
//recibe los valores del juego, un puntero a los cuadros, el arreglo de teselas levantadas de la rom y el arreglo de cuadros de textos
void imprimir_textos(juego_t * juego, imagen_t **cuadro, imagen_t *teselas[], imagen_t * cuadros_textos[CANTIDAD_CUADROS]);

#endif