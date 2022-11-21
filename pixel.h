#ifndef PIXEL_H
#define PIXEL_H

#include <stdint.h>
#include <stdbool.h>


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



typedef uint16_t pixel_t;


//recibe un valor de rojo r, de verde g y de azul b (o 0 o 1).
//devuelve un pixel_t con el formato de píxel de 3 bits.
pixel_t pixel3_crear(bool r, bool g, bool b);

//recibe un píxel de 3 bits
//devuelve las componentes RGB, cada una de 8 bits, por interfaz,
void pixel3_a_rgb(pixel_t pixel3, uint8_t *r, uint8_t *g, uint8_t *b);

//recibe un valor de rojo r, de verde g y de azul b (entre 0 y 15).
//devuelve un pixel_t con el formato de píxel de 12 bits.
pixel_t pixel12_crear(uint8_t r, uint8_t g, uint8_t b);

//recibe un pixel de 12 bits
//devuelve las componentes RGB, cada una de 8 bits, por interfaz.
void pixel12_a_rgb(pixel_t pixel12, uint8_t *r, uint8_t *g, uint8_t *b);

//función creada por el alumno para convertir pixeles a formato RGB444
uint16_t pixel_a_rgb444(pixel_t pixel);

#endif

/* 
    pixel_t es de 16 bits, pero usamos:

    PIXEL DE 3 BITS:        PIXEL DE 12 BITS:
    2             0         11                 8                                        0
    +----+----+----+        +----+----+----+----++----+----+----+----+----+----+----+----+
    | r0 | g0 | b0 |        | r3 | r2 | r1 | r0 || g3 | g2 | g1 | g0 | b3 | b2 | b1 | b0 |
    +----+----+----+        +----+----+----+----++----+----+----+----+----+----+----+----+

   Para corrimientos en el píxel de 3 bits se agregó un tipo enumerativo rgb3_t que reutilicé para las lecturas de las teselas

*/