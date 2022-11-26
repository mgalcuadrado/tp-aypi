#include <stdbool.h>
#include <stdio.h>
#include "roms.h"

#define MASK_MSB 0x80
#define MASK_LSB 0x1
#define CORRIMIENTO_MAX_UINT8T 7

#define CANTIDAD_ROMS_OG 3


//para leer_figuras 
#define MASK_4MSB 0xF000
#define SHIFT_BYTE 8



//para leer_ruta
#define MASK_4LSB 0xF
#define SHIFT_4LEC 4

#define SHIFT_4LEC 4

//para leer_figuras 
#define MASK_4MSB 0xF000
#define MASK_4LSB 0xF
#define SHIFT_BYTE 8

typedef enum{
    ARCHIVO_ROM_B,
    ARCHIVO_ROM_G,
    ARCHIVO_ROM_R,
    ARCHIVO_ROM_RUTA,
    ARCHIVO_ROM_FIGURA_1,
    ARCHIVO_ROM_FIGURA_2,
    ARCHIVO_ROM_FIGURA_3,
    ARCHIVO_ROM_FIGURA_4,
    ARCHIVO_ROM_FIGURA_5,
    ARCHIVO_ROM_FIGURA_6,
    ARCHIVO_ROM_FIGURA_7,
    ARCHIVO_ROM_FIGURA_8,
    ARCHIVO_ROM_FIGURA_9,
    ARCHIVO_ROM_FIGURA_10,
    ARCHIVO_ROM_FIGURA_11,
    ARCHIVO_ROM_FIGURA_12,
    ARCHIVO_ROM_FIGURA_13,
    ARCHIVO_ROM_FIGURA_14,
}archivos_t;

const char *archivos_rom[CANTIDAD_ROMS] = {  
[ARCHIVO_ROM_R] = "roms/6841.rom",
[ARCHIVO_ROM_G] = "roms/6842.rom",
[ARCHIVO_ROM_B] = "roms/6843.rom",
[ARCHIVO_ROM_RUTA] = "roms/6840.rom",
[ARCHIVO_ROM_FIGURA_1] = "roms/6819.rom",
[ARCHIVO_ROM_FIGURA_2] = "roms/6820.rom",
[ARCHIVO_ROM_FIGURA_3] = "roms/6821.rom",
[ARCHIVO_ROM_FIGURA_4] = "roms/6822.rom",
[ARCHIVO_ROM_FIGURA_5] = "roms/6823.rom",
[ARCHIVO_ROM_FIGURA_6] = "roms/6824.rom",
[ARCHIVO_ROM_FIGURA_7] = "roms/6825.rom",
[ARCHIVO_ROM_FIGURA_8] = "roms/6826.rom",
[ARCHIVO_ROM_FIGURA_9] = "roms/6827.rom",
[ARCHIVO_ROM_FIGURA_10] = "roms/6828.rom",
[ARCHIVO_ROM_FIGURA_11] = "roms/6829.rom",
[ARCHIVO_ROM_FIGURA_12] = "roms/6830.rom",
[ARCHIVO_ROM_FIGURA_13] = "roms/6845.rom",
[ARCHIVO_ROM_FIGURA_14] = "roms/6846.rom",
};

static bool leer_teselas(imagen_t * teselas[]);
static bool leer_figuras(imagen_t * figuras[]);
static bool leer_ruta(imagen_t * ruta);


void roms_destruir (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta){
    for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
            imagen_destruir(figuras[i]);
        imagen_destruir(ruta);
}

/*
bool roms_inicializar(imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta){
    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);
        if (teselas[i] == NULL){
            fprintf(stderr, "generar teselas falló\n");
            for (size_t j = 0; j < i; j++)
                imagen_destruir(teselas[j]);
            return false;
        }
    }

    for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++){
        figuras[i] = imagen_generar(figura_get_ancho(i), figura_get_alto(i), 0);
        if (figuras[i] == NULL){
            fprintf(stderr, "generar figuras falló\n");
            for (size_t j = 0; j < CANTIDAD_TESELAS; j++)
                imagen_destruir(teselas[j]);
            for (size_t j = 0; j < i; j++)
                imagen_destruir(figuras[j]);
            return false;
        }
    }

    ruta = imagen_generar(ANCHO_RUTA, ALTO_RUTA_NUEVO, 0);
    if (ruta == NULL){
        fprintf(stderr, "generar ruta falló\n");
        roms_destruir(teselas, figuras, ruta);
        return false;
    }

    return true;
}
*/

bool roms_levantar (imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta){
    if(!leer_teselas(teselas)){
        fprintf(stderr, "No se pudieron leer las teselas\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        return false;
    }
    
    if (!leer_figuras(figuras)){
        fprintf(stderr, "No se pudieron leer las figuras\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
            imagen_destruir(figuras[i]);
        return false;
    } 

    if (!leer_ruta(ruta)){
        fprintf(stderr, "No se pudieron leer las rutas\n");
        roms_destruir(teselas, figuras, ruta);
        return false;
    }

    return true;
} 



//función interna creada por el alumno para sumar en las teselas los valores dados por cada archivo.
//recibe un archivo abierto en formato de lectura binaria y el puntero al arreglo de imágenes teselas (no cierra el archivo).
static bool _sumar_teselas(FILE * f, imagen_t *teselas[], size_t corrimiento/*, size_t cant_bits*/){
    for (size_t a = 0; a < CANTIDAD_TESELAS; a++){
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



static bool leer_ruta(imagen_t * ruta){
    FILE * archivo = fopen (archivos_rom[ARCHIVO_ROM_RUTA], "rb");
    if (archivo == NULL){
        fprintf(stderr, "para ruta no se pudo abrir el archivo de lectura\n");
        return false;
    }
    for (size_t i = 0; i < CANTIDAD_RUTAS; i++){ 
        uint8_t n[16  * ANCHO_RUTA / 8];
        if (fread(n, sizeof(uint8_t), 16 * ANCHO_RUTA / 8, archivo) != 16 * ANCHO_RUTA / 8){
            fprintf(stderr, "la ruta no se pudo leer por completo\n");
            fclose(archivo);
            return false;
        }
        for (size_t f = 0; f < ALTO_RUTA_NUEVO; f++){
                for (size_t c = 0; c < ANCHO_RUTA / 8; c ++){
                    uint8_t lec;
                    if (fread(&lec, sizeof(uint8_t), 1, archivo) != 1){
                        fprintf(stderr, "la ruta no se pudo leer por completo\n");
                        fclose(archivo);
                        return false;
                    }
                    for (size_t j = 0; j < 8; j++)
                        imagen_set_pixel(ruta, c * 8 + j, f, imagen_get_pixel(ruta, c * 8 + j, f) + (((lec >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB) << i)); 
                }
        }
        if (fread(n, sizeof(uint8_t), 16 * ANCHO_RUTA / 8, archivo) != 16 * ANCHO_RUTA / 8){
            fprintf(stderr, "la ruta no se pudo leer por completo\n");
            fclose(archivo);
            return false;
        }
    }
    imagen_guardar_ppm(ruta, "ruta40.ppm", pixel12_a_rgb);
    fprintf(stderr, "la ruta se guardó bien\n");
    return (fclose(archivo) != EOF);
}


bool prueba_ruta(imagen_t * ruta){

    FILE * archivo = fopen (archivos_rom[ARCHIVO_ROM_RUTA], "rb");
    if (archivo == NULL) return false;
    /*for (*/size_t r = 0; //r < CANTIDAD_RUTAS; r++){
        uint8_t n[16 * ANCHO_RUTA / 8];
        if (fread(n, sizeof(uint8_t), 16 * ANCHO_RUTA / 8, archivo) != 16 * ANCHO_RUTA / 8){
            fclose(archivo);
            return false;
        }
        for (size_t f = 0; f < ALTO_RUTA_NUEVO; f++){
            for (size_t c = 0; c < ANCHO_RUTA / 8; c++){
                uint8_t n;
                if (fread(&n, sizeof(uint8_t), 1, archivo) != 1){
                    fclose(archivo);
                    return false;
                }
                for (size_t j = 0; j < 8; j++){
                    imagen_set_pixel(ruta, c * 8 + j, f, imagen_get_pixel(ruta, c * 8 + j, f) + (((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB) << r)); 
                }
            }
        }
        if (fread(n, sizeof(uint8_t), 16 * ANCHO_RUTA / 8, archivo) != 16 * ANCHO_RUTA / 8){
            fclose(archivo);
            return false;
        }
    fclose(archivo);
    imagen_guardar_ppm(ruta, "rutamil.ppm", pixel12_a_rgb);
    return true;
}



static bool leer_figuras (imagen_t * figuras[]){
    uint16_t rom[229376];
    for (size_t a = 4, i = 0; a < CANTIDAD_ROMS && i < 229376; a += 2, i += (229376 / 7)){
        FILE * bajo = fopen (archivos_rom[a], "rb");
        if (bajo == NULL){
            fprintf(stderr, "no se pudo abrir el archivo %s\n", archivos_rom[a - 1]);
            return false;
        }
        FILE * alto = fopen (archivos_rom[a + 1], "rb");
        if (alto == NULL){
            fprintf(stderr, "no se pudo abrir el archivo %s\n", archivos_rom[a]);
            fclose(bajo);
            return false;
        }
        for (size_t byte = 0; byte < 32768; byte++){
            uint8_t b, a;
            if ((fread (&b, sizeof(uint8_t), 1, bajo) != 1) || fread(&a, sizeof(uint8_t), 1, alto) != 1){
                fprintf(stderr, "falló la lectura del byte %zd por el archivo este o uno menos %d\n", byte, a);
                fclose(bajo);
                fclose (alto);
                return false;
            }
            rom [byte + i] = (a << SHIFT_BYTE) | b;
        }
        if (fclose(bajo) == EOF){
            fprintf(stderr, "cerró mal el archivo %s\n", archivos_rom[a - 1]);
            fclose(alto);
            return false;
        }
        if (fclose(alto) == EOF){
            fprintf(stderr, "cerró mal el archivo %s\n", archivos_rom[a]);
            return false;
        }
    }
///*
    for (figs_t fig = 0; fig < CANTIDAD_FIGURAS; fig++){
        size_t in = figura_get_inicio(fig), iter_ancho = (figura_get_ancho(fig) / 4) + ((figura_get_ancho(fig) % 4 != 0) ? 1 : 0);

        for(size_t f = 0; f < figura_get_alto(fig); f++){
            bool new_line = false;
            size_t x = 0;
            for(size_t col = 0; /*!new_line && */ col < iter_ancho; col++){
                uint16_t n = rom[in++];
                for (size_t i = 0; i < 4; i++){
                  if (((n & (MASK_4MSB >> SHIFT_4LEC)) == (MASK_4MSB >> SHIFT_4LEC)) && ((n & MASK_4LSB) == MASK_4LSB) && x == 0){
                        new_line = true;
                        f--;
                        break;
                    }
                    if (x < figura_get_ancho(fig)){
                        if (i == 3 && (n & MASK_4LSB) == MASK_4LSB) {
                            new_line = true;
                            break;
                        }
                        imagen_set_pixel(figuras[fig], x, f, (n & (MASK_4MSB >> i * 4)) >> (SHIFT_BYTE + SHIFT_4LEC - i * 4));
                        x += 1;
                    }
                    if (x == figura_get_ancho(fig)){
                        new_line = true;
                    }
                }
                if (new_line) break;
            }
        }
    }
    return true;
}
//*/

/*
 for (figs_t fig = 0; fig < 13; fig++){
        bool new_line = false;
        for (size_t f = 0; f < figura_get_alto(fig); f++){
            for (size_t c = 0, x = 0; c < figura_get_ancho(fig) / 4; c++){
                uint16_t n = rom[figura_get_inicio(fig) + f * figura_get_ancho(fig) / 4 + c];
                for (size_t i = 0; i < 4; i++){
                  // if ((n & (MASK_4LSB << 12) == (MASK_4LSB << 12)) && ((n & MASK_4LSB) == MASK_4LSB)){
                      //  new_line = true;
                      //  break;
                   // } 
                    if (i == 3 && (n & MASK_4LSB) == MASK_4LSB) {
                        new_line = true;
                        break;
                    }
                    imagen_set_pixel(figuras[fig], x++, f, (n & (MASK_4MSB >> i * 4)) >> (SHIFT_BYTE + SHIFT_4LEC - i * 4));
                    new_line = false;
                }
                if (new_line) break;
            }
        }
    }
    return true;
}
//*/

bool prueba_figuras(void){
    imagen_t * im = imagen_generar(8, 9, 0);
    //valida magoya
    //bool new_line = false;
    uint16_t prueba[18] = {0xf0fe, 0x0f0f, 0xf0ee, 0xef0f, 0xf07e, 0x170f, 0xf422, 0x440f, 0xfabb, 0xae0f, 0xf05b, 0x240f, 0xf04c, 0x7b0f, 0xf0b9, 0xba0f, 0xf0ab, 0xaf0f};
    for (size_t f = 0; f < 9; f++){
            for (size_t c = 0, x = 0; c < 8 / 4; c++){
                uint16_t n = prueba[f * 2 + c];
                for (size_t i = 0; i < 4; i++){
                  /* if ((n & (MASK_4LSB << 12) == (MASK_4LSB << 12)) && ((n & MASK_4LSB) == MASK_4LSB)){
                        new_line = true;
                        break;
                    } */
                    if (i == 3 && (n & MASK_4LSB) == MASK_4LSB) {
                        //new_line = true;
                        break;
                    }
                    imagen_set_pixel(im, x++, f, (n & (MASK_4MSB >> i * 4)) >> (SHIFT_BYTE + SHIFT_4LEC - i * 4));
                    //new_line = false;
                }
               // if (new_line) break;
            }
    }
   // imagen_guardar_ppm (im, "prueba.ppm", pixel3_a_rgb);
    imagen_destruir(im);
    return true;
}


static bool leer_teselas(imagen_t *teselas[]){
    for (size_t color = 0; color < CANTIDAD_ROMS; color++){
        FILE * lectura = fopen(archivos_rom[color], "rb");
        if (lectura == NULL) return false;
        if (color < CANTIDAD_ROMS_OG){
            if (!_sumar_teselas(lectura, teselas, color)) return false;
        }
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
