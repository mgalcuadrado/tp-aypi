#ifndef TESELAS_H
#define TESELAS_H

#include <stdint.h>
#include "paleta.h"
#include "imagen.h"
#include "figuras.h"


bool leer_figuras(imagen_t * figuras[]);
/**/
bool prueba_figuras(void);

bool prueba_ruta(imagen_t * ruta);

bool leer_teselas(imagen_t *teselas[]);

bool leer_ruta(imagen_t * ruta);
/**/
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);

#endif
