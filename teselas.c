
#define MASK_MSB 0x80
#define MASK_LSB 0x1
#define CORRIMIENTO_MAX_UINT8T 7

#define CANTIDAD_ROMS 3

const char * archivos_rom[CANTIDAD_ROMS] = {
    [0] = ARCHIVO_ROM_B,
    [1] = ARCHIVO_ROM_G,
    [2] = ARCHIVO_ROM_R
};

bool _sumar_teselas(FILE * f, imagen_t * teselas[], size_t corrimiento);
bool leer_teselas(imagen_t *teselas[]);
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);


/************************* FUNCIONES *************************************/

bool leer_teselas(imagen_t *teselas[]){
    for (size_t color = 0; color < CANTIDAD_ROMS; color++){
        FILE * lectura = fopen(archivos_rom[color], "rb");
        if (lectura == NULL) return false;
        if (color < CANTIDAD_ROMS_PIXEL3){
            if (! _sumar_teselas(lectura, teselas, color)) return false;
        }
        else{
            //funcion nueva leer_figuras(teselas[])
        }
        if (fclose(lectura)) return false;
    }
    return true;
}

//función interna creada por el alumno para sumar en las teselas los valores dados por cada archivo.
//recibe un archivo abierto en formato de lectura binaria y el puntero al arreglo de imágenes teselas (no cierra el archivo).
bool _sumar_teselas(FILE * f, imagen_t * teselas[], size_t corrimiento, /*size_t cant_bits*/){
    for (size_t a = 0; a < CANTIDAD_TESELAS; a++){
        for (size_t i = 0; i < imagen_get_alto(teselas[a]); i++){ 
            uint8_t n;             if (fread(&n, sizeof(n), 1, f) != 1) return false;
            for (size_t j = 0; j < imagen_get_ancho(teselas[a]); j++)
               imagen_set_pixel(teselas[a], j, i, imagen_get_pixel(teselas[a], j, i) + (((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB) << corrimiento)); 
               //imagen_set_pixel(teselas[a], j, i, (imagen_get_pixel(teselas[a], j, i)) << 1 + ((n >> (CORRIMIENTO_MAX_UINT8T - j)) & MASK_LSB)); 
        }
    }
    return true;
} // n >> (CORRIMIENTO_MAX - j) traslada la lectura a derecha para que el bit buscado quede en la posición 0x01. 
  // El resultado del and con la máscara del LSB se traslada a izquierda para que se guarde en la posición del color que se está leyendo.



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
