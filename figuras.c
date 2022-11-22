
#include "figuras.h"
#include <stdio.h>

#define SHIFT_4LEC 4

//para leer_figuras 
#define MASK_4MSB 0xF000
#define MASK_4LSB 0xF
#define SHIFT_BYTE 8


bool leer_figuras (imagen_t * figuras[]){
    uint16_t rom[229376];
    for (size_t a = 5, i = 0; a < CANTIDAD_ROMS; a += 2, i += 32768){
        FILE * bajo = fopen (archivos_rom[a - 1], "rb");
        if (bajo == NULL) return false;
        FILE * alto = fopen (archivos_rom[a], "rb");
        if (alto == NULL){
            fclose(bajo);
            return false;
        }
        for (size_t byte = 0; byte < 32768; byte++){
            uint8_t b, a;
            if ((fread (&b, sizeof(uint8_t), 1, bajo) != 1) || fread(&a, sizeof(uint8_t), 1, alto) != 1){
                fclose(bajo);
                fclose (alto);
                return false;
            }
            rom [byte + i] = (a << SHIFT_BYTE) | b;
        }
        if (fclose(bajo) == EOF){
            fclose(alto);
            return false;
        }
        if (fclose(alto) == EOF) return false;
    }
    for (enumfigs_t fig = 0; fig < 13; fig++){
        for (size_t f = 0; f < arr_pos_figuras[fig].alto; f++){
            for (size_t c = 0, x = 0; c < arr_pos_figuras[fig].ancho / 4; c++){
                uint16_t n = rom[arr_pos_figuras[fig].inicio + f * arr_pos_figuras[fig].ancho + c];
                for (size_t i = 0; i < 4; i++){
                    if (i == 3 && (n & MASK_4LSB) == MASK_4LSB) break;
                    imagen_set_pixel(figuras[fig], x++, f, (n & (MASK_4MSB >> i * 4)) >> (SHIFT_BYTE + SHIFT_4LEC - i * 4));
                }
            }    
        }
    }
}
