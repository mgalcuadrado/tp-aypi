#ifndef IMAGEN_H
#define IMAGEN_H

#include "pixel.h"
#include <stdio.h>
#include "config.h"


typedef struct imagen imagen_t;


//esta función recibe una imagenn y libera la memoria asociada a la misma
void imagen_destruir (imagen_t *imagen);

//La función se hizo para destruir 3 imagenes a la vez y no llenar de codigo
void imagen_destruir_mas(imagen_t *im1, imagen_t *im2, imagen_t *im3);

//la función devuelve una imagen de ancho x alto con todos los pixeles inicializados en un valor
imagen_t *imagen_generar (size_t ancho, size_t alto, pixel_t valor);

//esta función devuelve una imagen de ancho_destino x alto_destino escalada a partir de la imagen origen
imagen_t *imagen_escalar (const imagen_t *origen, size_t ancho_destino, size_t alto_destino);

//esta función copia desde las coordenadas (x, y) de destino la imagen origen
void imagen_pegar (imagen_t *destino, const imagen_t *origen, int x, int y);

//esta función pega en la imagen de destino la imagen de origen a partir del punto (x,y) de destino con los colores asignados por paleta para los píxeles
void imagen_pegar_con_paleta(imagen_t *destino, const imagen_t *origen, int x, int y, const pixel_t paleta[]);

//recibe la imagen, devuelve el ancho por el nombre
size_t imagen_get_ancho(const imagen_t *im);

//recibe la imagen, devuelve el alto por el nombre
size_t imagen_get_alto(const imagen_t *im);

//devuelve el píxel de la imagen im que se encuentra en la posición (x,y)
//se impone como precondición que 0 <= x < ancho y que 0 <= y < alto
pixel_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y);

//en la posición (x,y) de la imagen im guarda el valor p.
//devuelve un booleano indicando si se pudo realizar la operación
bool imagen_set_pixel(const imagen_t *im, size_t x, size_t y, pixel_t p);

//recibe una imagen para copiar en un archivo ya abierto en modo escritura y texto. También recibe un puntero a una función para obtener a partir de un pixel_t las componentes rgb
//escribe en el archivo la imagen en formato PPM con sus valores RGB correspondientes (no cierra el archivo)
void imagen_escribir_ppm(const imagen_t *im, FILE *fo, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t * ));

//recibe una imagen para copiar en un archivo no abierto con ruta fn y un puntero a una función para obtener de un pixel_t las componentes rgb
//escribe en el archivo la imagen en formato PPM con sus valores RGB correspondientes
bool imagen_guardar_ppm(const imagen_t *im, const char *fn, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *));

//COMENTAR CÓMO FUNCIONA //TP
void imagen_a_textura(const imagen_t *im, uint16_t *v);

//COMENTAR CÓMO FUNCIONA //TP
bool imagen_redimensionar(imagen_t * im, size_t n_ancho, size_t n_alto);

//Esta función recibe una imagen y devuelve por el nombre esa imagen reflejada
imagen_t * imagen_reflejar (imagen_t * im);

//Esta funcion es similar a la de mismo nombre, pero tiene unos cambios para asi pegar la ruta correctamente
void imagen_pegar_ruta_con_paleta(imagen_t * destino, const imagen_t *origen, int x, int y, const pixel_t paleta[]);

//imagen pintar recibe una imagen im y le asigna a todos los pixeles de esa imagen un valor pasado como parámetro
void imagen_pintar (imagen_t * im, int valor);

#endif