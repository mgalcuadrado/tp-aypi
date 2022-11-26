#ifndef ROMS_H
#define ROMS_H

#include <stdint.h>
#include "paleta.h"
#include "imagen.h"
#include "figuras.h"

// esta función recibe arreglos de imagen_ts para teselas y figuras y una imagen_t ruta cuya memoria NO FUE PEDIDA
// y devuelve 

bool roms_levantar (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta);

//
void roms_destruir (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta);

/**/
bool prueba_figuras(void);

bool prueba_ruta(imagen_t * ruta);

/**/
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);

#endif
