#include "imagen.h"
#include <stdint.h>
#include <stdio.h> //para manejo de archivos
#include <stdbool.h>
#include <stdlib.h> //para malloc() y free()

#define MENSAJE_FORMATO "P3\n" 
#define MAXIMO_PPM 255 

struct imagen{
    pixel_t **pixeles;
    size_t ancho, alto;
    //inv. de representación: imagen guarda una matriz de pixel_ts pixeles de ancho x alto
};

//esta función interna creada por el alumno recibe una matriz dinámica de píxeles y el alto de la misma.
//Libera la memoria asociada a la matriz pixeles.
static void _pixeles_destruir (size_t alto, pixel_t **pixeles){
    for (size_t i = 0; i < alto; i++)
            free (pixeles[i]);
    free (pixeles);    
}

void imagen_destruir (imagen_t *imagen){
    _pixeles_destruir (imagen->alto, imagen->pixeles); 
    free (imagen);
}

static imagen_t * _imagen_crear (size_t ancho, size_t alto){
    imagen_t * imagen = malloc (sizeof(imagen_t));
    if (imagen == NULL) 
        return NULL;
    imagen -> pixeles = malloc (alto * sizeof(pixel_t*)); 
    if (imagen -> pixeles == NULL){
        free(imagen);
        return NULL;
    }
    for (size_t i = 0; i < alto; i++){
        imagen -> pixeles[i] = malloc (ancho * sizeof(pixel_t));
        if (imagen -> pixeles[i] == NULL){
            _pixeles_destruir (i, imagen -> pixeles);
            free (imagen);
            return NULL;
        }
    }
    imagen -> ancho = ancho;
    imagen -> alto  = alto;
    return imagen;
}

imagen_t *imagen_generar (size_t ancho, size_t alto, pixel_t valor){
    imagen_t * imagen = _imagen_crear(ancho, alto);
    if (imagen == NULL)
        return NULL;
    for (size_t i = 0; i < imagen->alto; i++){
        for (size_t j = 0; j < imagen->ancho; j++)
            imagen->pixeles[i][j] = valor;
    }
    return imagen;
}



imagen_t *imagen_escalar (const imagen_t *origen, size_t ancho_destino, size_t alto_destino){
    imagen_t * destino = _imagen_crear(ancho_destino, alto_destino);
    if (destino == NULL) return NULL;
    float escalar_alto = (float) origen->alto / destino->alto;
    float escalar_ancho = (float) origen->ancho / destino->ancho;
    for (size_t i = 0; i < destino->alto; i++){
        for (size_t j = 0; j < destino->ancho; j++){
            if (((i * escalar_alto) < origen->alto) && ((j * escalar_ancho) < origen->ancho)){
                destino->pixeles[i][j] = origen->pixeles[(int) (i * escalar_alto)][(int) (j * escalar_ancho)]; 
            }
        }
    }
    return destino;
}

void imagen_pegar (imagen_t *destino, const imagen_t *origen, int x, int y){
    for(int f = (y >= 0 ? 0 : -y); f < origen->alto && f + y < destino->alto; f++){
        for(int c = (x >= 0 ? 0 : -x); c < origen->ancho && c + x < destino->ancho; c++)
            if (origen -> pixeles[f][c] != 0){ 
                destino->pixeles[y + f][x + c] = origen->pixeles[f][c]; 
            } 
    }
}       

void imagen_pegar_con_paleta(imagen_t *destino, const imagen_t *origen, int x, int y, const pixel_t paleta[]){
for(int f = (y >= 0 ? 0 : -y); f < origen->alto && f + y < destino->alto; f++){
        bool pixeles_pegados = false;
        for(int c = (x >= 0 ? 0 : -x); c < origen->ancho && c + x < destino->ancho; c++){
            if (origen->pixeles[f][c] == 0 || origen->pixeles[f][c] == 0xF){
                pixeles_pegados = false;
            }
            else if (origen->pixeles[f][c] != 0 && (origen->pixeles[f][c] != 0xF || pixeles_pegados)){ 
                destino->pixeles[y + f][x + c] = paleta[origen->pixeles[f][c]]; 
                pixeles_pegados = true;
            } 
        }
    }
}

//Condiciones del pegar_ruta
static bool condiciones_pegar_ruta(const imagen_t *origen, int f , int c){
	if(origen->pixeles[f][c + 5 > origen->ancho ? c : c + 5] == 0)
		return false;
	if(origen->pixeles[f][c + 5 > origen->ancho ? c : c + 5] == 0xf)
		return false;
	if(origen->pixeles[f][c - 5 < 0 ? c : c - 5] == 0)
		return false;
	if(origen->pixeles[f][c - 5 < 0 ? c : c - 5] == 0xf)
		return false;
	return true;
}

void imagen_pegar_ruta_con_paleta(imagen_t * destino, const imagen_t *origen, int x, int y, const pixel_t paleta[]){
    for(int f = (y >= 0 ? 0 : -y); f < origen->alto && f + y < destino->alto; f++){
        bool pixeles_pegados = false;
        for(int c = (x >= 0 ? 0 : -x); c < origen->ancho && c + x < destino->ancho; c++){
            if ((origen->pixeles[f][c] == 0 || (origen->pixeles[f][c] == 0xF))){
                if(condiciones_pegar_ruta(origen, f, c))
                    pixeles_pegados = true;
                else
                    pixeles_pegados = false;
            }
            if (origen->pixeles[f][c] != 0 && ((origen->pixeles[f][c] != 0xF || pixeles_pegados) )){ 
                destino->pixeles[y + f][x + c] = paleta[origen->pixeles[f][c]]; 
                pixeles_pegados = true;
            } 
        }
    }    
}

//recibe la imagen, devuelve el ancho por el nombre
size_t imagen_get_ancho(const imagen_t *im){
    return im->ancho;
}

//recibe la imagen, devuelve el alto por el nombre
size_t imagen_get_alto(const imagen_t *im){
    return im->alto;
}

//devuelve el píxel de imagen en la posición (x,y)
//se impone como precondición que 0 <= x < ancho y que 0 <= y < alto
pixel_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y){
    return im->pixeles[y][x];
}

//en la posición (x,y) de la imagen im guarda el valor p.
//devuelve un booleano indicando si se pudo realizar la operación
bool imagen_set_pixel(const imagen_t *im, size_t x, size_t y, pixel_t p){
    if ((x < 0) || (x >= im->ancho) ||(y < 0) || (y >= im->alto)) return false; 
    im->pixeles[y][x] = p;
    return true;
}

//recibe un archivo fo abierto en formato escritura y texto y escribe la imagen im en formato PPM.
void imagen_escribir_ppm(const imagen_t *im, FILE *fo, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t * )){
    fprintf(fo, "%s%zd %zd\n%d\n", MENSAJE_FORMATO, im->ancho, im->alto, MAXIMO_PPM);
    uint8_t r, g, b;
    for (size_t i = 0; i < im->alto; i++){
        for (size_t j = 0; j < im->ancho; j++){
            pixel_a_rgb(im->pixeles[i][j], &r, &g, &b);
            fprintf(fo, "%d %d %d\n", r, g, b);
        }
    }
}

bool imagen_guardar_ppm(const imagen_t *im, const char *fn, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *)){
    FILE * f = fopen(fn, "wt");
    if (f == NULL) return false;
    imagen_escribir_ppm(im, f, pixel_a_rgb);
    if (fclose(f)) return false;
    return true;
}

//convierte una imagen im en un arreglo v de uint16_ts
void imagen_a_textura(const imagen_t *im, uint16_t *v){
    for (size_t f = 0; f < im->alto; f++)
        for (size_t c = 0; c < im->ancho; c++)
            v[(f * im->ancho) + c] = im->pixeles[f][c];
}

//Esta funcion refleja las imagenes
imagen_t * imagen_reflejar (imagen_t * im){
    imagen_t * ref = imagen_generar(im->ancho, im->alto, 0);
    if (ref == NULL) return NULL;
    ref->ancho = im->ancho;
    ref->alto = im->alto;
    for (size_t f = 0; f < im->alto; f++)
        for (size_t c = 0; c < im->ancho; c++)
            ref->pixeles[f][c] = im->pixeles[f][(im->ancho - 1) - c];
    return ref;
}

//un destructor con 3 argumentos para que ocupe menos líneas de código la destrucción
void imagen_destruir_mas(imagen_t *im1, imagen_t *im2, imagen_t *im3){
    imagen_destruir(im1);
    imagen_destruir(im2);
    imagen_destruir(im3);
}

void imagen_pintar (imagen_t * im, int valor){
    for (size_t f = 0; f < im->alto; f++)
        for (size_t c = 0; c < im->ancho; c++)
            im->pixeles[f][c] = valor;
}