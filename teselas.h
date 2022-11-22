#ifndef TESELAS_H
#define TESELAS_H

#include <stdint.h>
#include "paleta.h"
#include "imagen.h"



/**/
bool leer_teselas(imagen_t *teselas[]);

/**/
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);

#endif
