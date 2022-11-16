#include "pixel.h"

#include <stdio.h>

//etiquetas para los píxeles de 3 bits
#define MASK_PIXEL_3R 0x4
#define MASK_PIXEL_3G 0x2
#define MASK_PIXEL_3B 0x1

#define SHIFT_PIXEL_3R 2
#define SHIFT_PIXEL_3G 1

//etiquetas para los píxeles de 12 bits
#define MASK_PIXEL_12R 0xF00
#define MASK_PIXEL_12G 0x0F0
#define MASK_PIXEL_12B 0x00F

#define SHIFT_PIXEL_12R 8
#define SHIFT_PIXEL_12G 4

#define SHIFT_RGB_12 4


//para los corrimientos se utiliza el tipo enumerativo rgb3_t definido en pixel.h
pixel_t pixel3_crear(bool r, bool g, bool b){
    return ((r  << SHIFT_PIXEL_3R) | (g << SHIFT_PIXEL_3G) | b);
}

// si el bit correspondiente al color está en 0 se le asigna un valor de 0, 
//mientras que si el bit está puesto en 1 se le asigna un valor de 255.
void pixel3_a_rgb(pixel_t pixel3, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = (pixel3 & MASK_PIXEL_3R) ? 255 : 0;
    *g = (pixel3 & MASK_PIXEL_3G) ? 255 : 0;
    *b = (pixel3 & MASK_PIXEL_3B) ? 255 : 0;
}

//recibe valores r g b entre 0 y 15
pixel_t pixel12_crear(uint8_t r, uint8_t g, uint8_t b){
    return ((r << SHIFT_PIXEL_12R) | (g << SHIFT_PIXEL_12G) | b);
}

//recibe un pixel de 12 bits
//devuelve las componentes RGB de 24 bits por interfaz
void pixel12_a_rgb(pixel_t pixel12, uint8_t *r, uint8_t *g, uint8_t *b){
    *r = ((pixel12 & MASK_PIXEL_12R) >> SHIFT_PIXEL_12R) << SHIFT_RGB_12;
    *g = ((pixel12 & MASK_PIXEL_12G) >> SHIFT_PIXEL_12G) << SHIFT_RGB_12;
    *b = (pixel12 & MASK_PIXEL_12B) << SHIFT_RGB_12;
}
