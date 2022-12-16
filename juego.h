#ifndef JUEGO_H
#define JUEGO_H

#include "moto.h"
#include <stddef.h>
#include "config.h"
#include "imagen.h"

typedef struct juego juego_t;

//Esta función se encarga de inicializar los parámetros del juego y devuelve un juego_t (en caso de falla, juego_t = NULL)
juego_t * juego_iniciar_parametros(void);

//Esta función se encarga de destruir los parámetros del juego
void juego_finalizar(juego_t * j);

//Getter del tiempo del juego
size_t juego_get_tiempo(juego_t *juego);

//Setter del tiempo del juego, recibe el TDA juego, la moto y el segundero del juego
void juego_set_tiempo(juego_t *juego, moto_t *moto, size_t t);

//Setter de la velocidad que se muestra en pantalla, recibe el TDA juego y la moto
void juego_set_speed(juego_t *juego, moto_t * moto);

//Setter de los puntajes del juego, recibe el TDA juego, la moto y la posicion anterior de la moto
void juego_set_puntajes(juego_t *juego, moto_t *moto, float x);

//Función que imprime los textos en pantalla
//Recibe los valores del juego, un puntero a los cuadros, el arreglo de teselas levantadas de la rom y el arreglo de cuadros de textos
void imprimir_textos(juego_t * juego, imagen_t **cuadro, imagen_t *teselas[], imagen_t * cuadros_textos[CANTIDAD_CUADROS]);

#endif