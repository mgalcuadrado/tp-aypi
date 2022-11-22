#include "figuras.c"

#include <stdbool.h>
#include <stdio.h>
#include "teselas.h"

#define MASK_MSB 0x80
#define MASK_LSB 0x1
#define CORRIMIENTO_MAX_UINT8T 7

#define CANTIDAD_ROMS 18
#define CANTIDAD_ROMS_OG 3

//para leer_ruta
#define MASK_4LSB 0xF
#define SHIFT_LEC4 4


const char * archivos_rom[CANTIDAD_ROMS] = {
    [0] = ARCHIVO_ROM_B,
    [1] = ARCHIVO_ROM_G,
    [2] = ARCHIVO_ROM_R,
    [3] = ARCHIVO_ROM_RUTA,
    [4] = ARCHIVO_ROM_FIGURA_1,
    [5] = ARCHIVO_ROM_FIGURA_2,
    [6] = ARCHIVO_ROM_FIGURA_3,
    [7] = ARCHIVO_ROM_FIGURA_4,
    [8] = ARCHIVO_ROM_FIGURA_5,
    [9] = ARCHIVO_ROM_FIGURA_6,
    [10] = ARCHIVO_ROM_FIGURA_7,
    [11] = ARCHIVO_ROM_FIGURA_8,
    [12] = ARCHIVO_ROM_FIGURA_9,
    [13] = ARCHIVO_ROM_FIGURA_10,
    [14] = ARCHIVO_ROM_FIGURA_11,
    [15] = ARCHIVO_ROM_FIGURA_12,
    [16] = ARCHIVO_ROM_FIGURA_13,
    [17] = ARCHIVO_ROM_FIGURA_14,
};

//función interna creada por el alumno para sumar en las teselas los valores dados por cada archivo.
//recibe un archivo abierto en formato de lectura binaria y el puntero al arreglo de imágenes teselas (no cierra el archivo).
static bool _sumar_teselas(FILE * f, imagen_t *teselas[], size_t corrimiento/*, size_t cant_bits*/){
    for (size_t a = 0; a < CANTIDAD_TESELAS_OG; a++){
        for (size_t i = 0; i < imagen_get_alto(teselas[a]); i++){ 
            uint8_t n;             
            if (fread(&n, sizeof(n), 1, f) != 1) return false;
            for (size_t j = 0; j < imagen_get_ancho(teselas[a]); j++)
               imagen_set_pixel(teselas[a], j, i, imagen_get_pixel(teselas[a], j, i) + (((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB) << corrimiento)); 
               //imagen_set_pixel(teselas[a], j, i, (imagen_get_pixel(teselas[a], j, i)) << 1 + ((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB)); 
        }
    }
    return true;
} // n >> (CORRIMIENTO_MAX - j) traslada la lectura a derecha para que el bit buscado quede en la posición 0x01. 
  // El resultado del and con la máscara del LSB se traslada a izquierda para que se guarde en la posición del color que se está leyendo.


static bool leer_ruta (imagen_t * teselas[]){
    FILE * archivo = fopen (ARCHIVO_ROM_RUTA, "rb");
    if (archivo == NULL) return false;
    /*for (*/ size_t i = CANTIDAD_TESELAS_OG + CANTIDAD_FIGURAS + 1; /* i < CANTIDAD_TESELAS_TOTAL; i++){ */
       // if (! imagen_redimensionar(teselas[i], ANCHO_RUTA, ALTO_RUTA)) return false;
        for (size_t f = 0; f < ALTO_RUTA; f++){
            //for (size_t color = 0; color < 4; color++){ // ???????
            for (size_t c = 0; c < ANCHO_RUTA; c += 8){
                uint8_t lec;
                if (fread(&lec, sizeof(uint8_t), 1, archivo) != 1){
                    fclose(archivo);
                    return false;
                }
                for (size_t j = 0; j < 8; j++)
               imagen_set_pixel(teselas[a], j + c, i, imagen_get_pixel(teselas[a], j, i) + ((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB)); 
               //imagen_set_pixel(teselas[a], j, i, (imagen_get_pixel(teselas[a], j, i)) << 1 + ((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB)); 

                //pixel_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y){
                //imagen_set_pixel(teselas[i], c - 1, f, imagen_get_pixel (teselas[i], c - 1, f) + ((lec >> SHIFT_LEC4) & MASK_4LSB));
                //[i]->pixeles[f][c - 1] = (lec >> SHIFT_LEC4) & MASK_4LSB;
                //imagen_set_pixel(teselas[i], c, f, imagen_get_pixel (teselas[i], c - 1, f) + (lec & MASK_4LSB));
                //teselas[i]->pixeles[f][c] = lec & MASK_4LSB;
           // }
            }
          //  }
    }
    return (fclose(archivo) != EOF);
}


#define MASK_LSBYTE 0xFF
#define SHIFT_BYTE 8
//ya tengo MASK_4LSB 0xF para D


static bool leer_figuras (imagen_t * figuras[]){
    uint16_t rom[229376];
    for (size_t a = 6, i = 0; a < CANTIDAD_ROMS; a += 2, i += 32768){
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
        for (size_t f = arr_pos_figuras[fig].inicio; f < arr_pos_figuras[fig].inicio + arr_pos_figuras[fig].alto; f++){
            for (size_t c = 0, x = 0; c < arr_pos_figuras[fig].ancho; c++, x += 4){
                uint16_t n = rom[f * arr_pos_figuras[fig].ancho + c];
                //((n >> (SHIFT_BYTE + SHIFT_LEC4)) & MASK_4LSB);

            }    
        }
    }
}


bool leer_teselas(imagen_t *teselas[]){
    for (size_t color = 0; color < CANTIDAD_ROMS; color++){
        FILE * lectura = fopen(archivos_rom[color], "rb");
        if (lectura == NULL) return false;
        if (color < CANTIDAD_ROMS_OG){
            if (!_sumar_teselas(lectura, teselas, color)) return false;
        }
        if (color == 4)
       /* if (! leer_ruta(teselas)) {
            fprintf(stderr, "ups :D\n");
            return false;
        }
        */
        if (fclose(lectura)) return false;
    }
    return true;
}



imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]){
    imagen_t * mosaico = imagen_generar(columnas * ANCHO_TESELA, filas * ALTO_TESELA, 0);
    if (mosaico == NULL) return NULL;
    for (size_t y = 0; y < filas; y++){
        for (size_t x = 0; x < columnas; x++){
            imagen_pegar_con_paleta(mosaico, teselas[mosaico_teselas[y][x]], x * ANCHO_TESELA, y * ALTO_TESELA, paleta[mosaico_paletas[y][x]]);  
        }
    } 
    return mosaico;
}
