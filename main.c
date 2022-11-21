#include <SDL2/SDL.h>
#include <stdbool.h>

#include "imagen.h"
#include "teselas.h"
#include "fondo.h"
#include "paleta.h"

#define MAX_CADENA 10

typedef enum{
    TOP,
    TIME,
    SCORE,
    STAGE,
    SPEED
}texto_t;

typedef struct{
    const char cadena[MAX_CADENA];
    size_t pos_x, pos_y; 
}sttexto_t;

sttexto_t textos[CANTIDAD_TEXTOS] = {
    [TOP] = {"TOP", 0x14, 0xe},
    [TIME] = {"TIME", 0x90, 0xe},
    [SCORE] = {"SCORE", 0xc6, 0xe},
    [STAGE] = {"STAGE", 0x14, 0x1c},
    [SPEED] = {"SPEED", 0xc6, 0x1c},
};

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Hang-On");

    SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STATIC, VENTANA_ANCHO, VENTANA_ALTO);
    uint16_t canvas[VENTANA_ALTO * VENTANA_ANCHO];

    int dormir = 0;

    // BEGIN código del alumno
    double x_moto = -10, x_fondo = 320;
    bool mover_derecha = false, mover_izquierda = false,
    acelerar = false, frenar = false;

    imagen_t *teselas[CANTIDAD_TESELAS_TOTAL];

    for(size_t i = 0; i < CANTIDAD_TESELAS_OG; i++)
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);
    for (size_t i = CANTIDAD_TESELAS_OG + CANTIDAD_FIGURAS; i < CANTIDAD_TESELAS_TOTAL; i++){
        teselas[i] = imagen_generar(ANCHO_RUTA, ALTO_RUTA, 0);
    }
    if(!leer_teselas(teselas)){
        fprintf(stderr, "No se pudieron leer las teselas\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS_TOTAL; i++)
            imagen_destruir(teselas[i]);
        return 1;
    }
    
    imagen_guardar_ppm(teselas[CANTIDAD_TESELAS_OG + CANTIDAD_FIGURAS + 1], "ruta1.ppm", pixel3_a_rgb);

    imagen_t *cuadro = imagen_generar(320, 224, 0xf);
    imagen_t *cielo = imagen_generar(320, 128,0xf);
    imagen_t *pasto = imagen_generar(1, 96, pixel12_crear(0, 13, 9));
    
    for(size_t i = 0; i < 10; i++)
        imagen_set_pixel(pasto, 0, i, colores_pasto[i]);

    imagen_t *pasto_estirado = imagen_escalar(pasto, 320, 96);
    imagen_destruir(pasto);
    
    imagen_t *fondo1 = generar_mosaico(teselas, paleta_3, FONDO1_FILAS, FONDO1_COLUMNAS, fondo1_mosaico, fondo1_paleta);
    imagen_t *fondo2 = generar_mosaico(teselas, paleta_3, FONDO2_FILAS, FONDO2_COLUMNAS, fondo2_mosaico, fondo2_paleta);
    
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        acelerar = true;
                        break;
                    case SDLK_DOWN:
                        frenar = true;
                        break;
                    case SDLK_RIGHT:
                        mover_derecha = true;
                        break;
                    case SDLK_LEFT:
                        mover_izquierda = true;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        acelerar = false;
                        break;
                    case SDLK_DOWN:
                        frenar = false;
                        break;
                    case SDLK_RIGHT:
                        mover_derecha = false;
                        break;
                    case SDLK_LEFT:
                        mover_izquierda = false;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno       

        imagen_pegar(cuadro,cielo,0,0);
        
        for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
            for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
                imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[i]);
        }
        
        /*Acà irìa la generaciòn de la ruta*/
        
        if (mover_izquierda){
            x_moto-= 1;
            x_fondo += 10;
        }
        if (mover_derecha){
            x_moto += 1;
            x_fondo -= 10;
        }
        
        if(x_moto > 320)
            x_moto = -10;
        else if(x_moto < (-11))
            x_moto = 320;
        if(x_fondo < -2048)
            x_fondo = 640;
        else if(x_fondo > 640)
            x_fondo = -2048;
        
        /*Seguro todos estos ifs se pueden mejorar xD*/

        imagen_pegar(cuadro, pasto_estirado, 0, 128);       

        imagen_pegar(cuadro, fondo2, (x_fondo * 0.75) + 320, 64);
        imagen_pegar(cuadro, fondo1, x_fondo + 320, 112);

        //esto sería la moto
        imagen_t *cuadrado = imagen_generar(10, 10, 0x0f0);
        imagen_pegar(cuadro, cuadrado, x_moto, (224 - 10) / 2);
        imagen_destruir(cuadrado);

        // Procedemos a dibujar a pantalla completa:
        imagen_t *cuadro_escalado = imagen_escalar(cuadro, VENTANA_ANCHO, VENTANA_ALTO);
        // Hay que implementar esta función que dibuja de forma eficiente:
        imagen_a_textura(cuadro_escalado, canvas);
        /*
        // Como todavía no la tenemos lo hacemos de forma ineficiente con primitivas:
        for(size_t f = 0; f < imagen_get_alto(cuadro_escalado); f++)
            for(size_t c = 0; c < imagen_get_ancho(cuadro_escalado); c++)
                canvas[f * imagen_get_ancho(cuadro_escalado) + c] = imagen_get_pixel(cuadro_escalado, c, f);
        // Implementar imagen_a_textura() cuanto antes!
        */

        imagen_destruir(cuadro_escalado);

        // END código del alumno

        SDL_UpdateTexture(texture, NULL, canvas, VENTANA_ANCHO * sizeof(uint16_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        else
            printf("Perdiendo cuadros\n");
        ticks = SDL_GetTicks();
    }


    // BEGIN código del alumno
    imagen_destruir(cuadro);
    imagen_destruir(fondo1);
    imagen_destruir(fondo2);
    imagen_destruir(cielo);

    for(size_t i = 0; i < CANTIDAD_TESELAS_TOTAL; i++)
        imagen_destruir(teselas[i]);

    imagen_destruir(pasto_estirado);

    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

