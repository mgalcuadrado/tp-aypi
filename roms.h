#ifndef ROMS_H
#define ROMS_H

#include "paleta.h"
#include "imagen.h"
#include "figuras.h"

#include <stdint.h>

//Esta función recibe arreglos de imagen_t's para teselas y figuras y una imagen_t ruta cuya memoria fue pedida previamente
//devuelve false en caso de falla
bool roms_levantar (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta);

//Funcion que destruye las teselas, figuras y las roms
void roms_destruir (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta);

//Función que recibe un mosaico de imagenes incluidas en teselas con su respectiva paleta y las unifica en una imagen_t imagen
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);

#endif
