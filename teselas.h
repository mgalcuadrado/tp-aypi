#ifndef TESELAS_H
#define TESELAS_H

#include <stdint.h>
#include "imagen.h"
#include "paleta.h"

/*Mechi, te dejo las explicaciones porque sos mejor explicando*/
//bool _sumar_teselas(FILE * f, imagen_t * teselas[], size_t corrimiento);

/**/
bool leer_teselas(imagen_t *teselas[]);

/**/
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);

#endif
