#include <SDL2/SDL.h>
#include <stdbool.h>

#include "imagen.h"
#include "teselas.h"
#include "fondo.h"
#include "paleta.h"
#include "figuras.h"
#include "moto.h"

#define MAX_CADENA 15

typedef enum{
    TOP,
    TIME,
    SCORE,
    STAGE,
    SPEED,
    KM
}texto_t;

typedef struct{
    const char cadena[MAX_CADENA];
    size_t pos_x, pos_y, paleta;
}sttexto_t;

const sttexto_t textos[CANTIDAD_TEXTOS] = {
    [TOP] = {"TOP", 0x14, 0xe, 8},
    [TIME] = {"TIME", 0x90, 0xe, 6},
    [SCORE] = {"SCORE", 0xc6, 0xe, 7},
    [STAGE] = {"STAGE", 0x14, 0x1c, 5},
    [SPEED] = {"SPEED", 0xc6, 0x1c, 6},
    [KM] = {"KM", 0x10e, 0x1c, 6},
};



//Esta es una funcion auxiliar que imprime los diferentes tipos de numeros en la pantalla 
void numeros_a_pantalla(imagen_t *destino, imagen_t **origen, size_t i, int x, int y, size_t *text);

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
    size_t n_textos[CANTIDAD_TEXTOS] = {[TOP] = 10000,[TIME] = 75, [SCORE] = 100000, [STAGE] = 1, [SPEED] = 0}; //en este arreglo de size_ts se guardan los valores asociados a los textos        

    /*moto_t *moto;
    moto_set_x(moto,0);
    moto_set_pos(moto,0);
    moto_set_acelerar(moto,false);                          AAAAAAAAAAAAAAAAAAAAAAAAAAA
    moto_set_frenar(moto,false);
    moto_set_izq(moto,false);
    moto_set_der(moto,false);
    */
    double x_moto = 162, x_fondo = 320;
    bool mover_derecha = false, mover_izquierda = false,
    acelerar = false, frenar = false;
    short boton_presionado = 0;
    size_t t = 0;
 
    imagen_t *teselas[CANTIDAD_TESELAS];
    imagen_t *figuras[CANTIDAD_FIGURAS];
    imagen_t *ruta;
    

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);

    for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
        figuras[i] = imagen_generar(figura_get_ancho(i), figura_get_alto(i), 0);

    ruta = imagen_generar(ANCHO_RUTA, ALTO_RUTA_NUEVO, 0);
    


    if(!leer_teselas(teselas)){
        fprintf(stderr, "No se pudieron leer las teselas\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        return 1;
    }
    prueba_figuras();
    
    if (!leer_figuras(figuras)){
        fprintf(stderr, "No se pudieron leer las figuras\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
            imagen_destruir(figuras[i]);
        return 1;
    }
   

    prueba_ruta(ruta);
    

    if (!leer_ruta(ruta)){
        fprintf(stderr, "No se pudieron leer las rutas\n");
        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);
        for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
            imagen_destruir(figuras[i]);
        imagen_destruir(ruta);
        return 1;
    }

    imagen_guardar_ppm(ruta, "rutatotal.ppm", pixel12_a_rgb);

    imagen_t *rutaza = imagen_reflejar(ruta);
    fprintf(stderr, "hasta acá llega piola\n");
    if (rutaza == NULL){
        fprintf(stderr, "che falló en reflejar\n");
        return 1;
    }
    
    fprintf(stderr, "rutaza es de %zd x %zd\n", imagen_get_ancho(rutaza), imagen_get_alto(rutaza));
    imagen_guardar_ppm(rutaza, "ruta0.ppm", pixel12_a_rgb);

    imagen_t *cuadro = imagen_generar(320, 224, 0);
    imagen_t *cielo = imagen_generar(320, 128, 0xf);
    imagen_t *pasto = imagen_generar(1, 96, pixel12_crear(0, 13, 9));
    imagen_t *cuadro_moto = imagen_generar(60, 73, 0);

    imagen_pegar_con_paleta(cuadro_moto, figuras[0], 0, 0, paleta_4[16]);

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
                //short aux = moto_get_pos(moto);           AAAAAAAAAAAAAAAAAAAAAAAA
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        //moto_set_acelerar(moto,true);     AAAAAAAAAAAAAAAAAAAAAAAAAA
                        acelerar = true;
                        break;
                    case SDLK_DOWN:
                        //moto_set_frenar(moto,true);       AAAAAAAAAAAAAAAAAAAAAAAAA
                        frenar = true;
                        break;
                    case SDLK_RIGHT:
                        /*moto_set_der(moto,true);
                        aux = moto_get_pos(moto);
                        moto_set_pos(moto,aux++);           AAAAAAAAAAAAAAAAAAAAAAAAA
                        if(aux > 2)
                            moto_set_pos(moto,3);*/
                        mover_derecha = true;
                        if(boton_presionado++ > 2)
                            boton_presionado = 3;
                        break;
                    case SDLK_LEFT:
                        /*moto_set_izq(moto,true);
                        aux = moto_get_pos(moto);
                        moto_set_pos(moto,aux++);           AAAAAAAAAAAAAAAAAAAAA
                        if(aux > 2)
                            moto_set_pos(moto,3);*/
                        mover_izquierda = true;
                        if(boton_presionado++ > 2)
                            boton_presionado = 3;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        /*moto_set_acelerar(moto,false);        AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        moto_set_pos(moto,0);*/
                        acelerar = false;
                        boton_presionado = 0;
                        break;
                    case SDLK_DOWN:
                        /*moto_set_frenar(moto,false);          AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        moto_set_pos(moto,0);*/
                        frenar = false;
                        boton_presionado = 0;
                        break;
                    case SDLK_RIGHT:
                        /*moto_set_der(moto,false);             AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        moto_set_pos(moto,0);*/
                        mover_derecha = false;
                        boton_presionado = 0;
                        break;
                    case SDLK_LEFT:
                        /*moto_set_izq(moto,false);             AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                        moto_set_pos(moto,0);*/
                        mover_izquierda = false;
                        boton_presionado = 0;
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno       

        imagen_pegar(cuadro, cielo, 0, 0);
        n_textos[TIME] = 75 - (t++ / JUEGO_FPS);
        
        //impresión de textos:
        for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
            for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
                imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[textos[i].paleta]);
            if(i < (CANTIDAD_TEXTOS - 1))
                numeros_a_pantalla(cuadro, teselas, i, 8 + textos[i].pos_x,textos[i].pos_y,n_textos);
        }

        /* CALCULO EL METRO DE LA RUTA QUE VA                     
                                                                AAAAAAAAAAAAAAAAAAAAAAAAAA
        moto_set_x(moto,moto_get_x(moto) + (moto_get_vel(moto) * (60.0/1000)))*/


        
        /*Acà irìa la generaciòn de la ruta*/

        /*if(moto_get_izq)) x_fondo += 10;                  AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        if(moto_get_izq)) x_fondo -= 10;*/
        if (mover_izquierda) x_fondo += 10; 
        if (mover_derecha) x_fondo -= 10;

        if(t % (JUEGO_FPS/(JUEGO_FPS /2))){

            /* //Desaceleración
            if(!moto_get_acelerar(moto) && !moto_get_frenar(moto) && moto_get_vel(moto) >= 80){ 
                moto_set_vel(moto,n_textos[SPEED] - 90/JUEGO_FPS);                   
                                                                    AAAAAAAAAAAAAAAAA
                //Pegar moto con paleta 0 y 1
            }*/
            
            if(acelerar == false && frenar == false && n_textos[SPEED] >= 80){ //Desaceleración
                n_textos[SPEED] -= 90/JUEGO_FPS;
                
                //Pegar con paleta 0 y 1
            }

            /*//Aceleración
            if((moto_get_acelerar(moto) || moto_get_vel(moto) < 80) && !moto_get_frenar(moto)){
                moto_set_vel(moto,279 - ((279 - (n_textos[SPEED])) * exp(-0.224358 * ((float)1/JUEGO_FPS))));
                                                    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
                //Pegar con paleta 0 y 1
            }*/

            if((acelerar == true || n_textos[SPEED] < 80) && frenar == false){ //Aceleración
                n_textos[SPEED] = 279 - ((279 - (n_textos[SPEED])) * exp(-0.224358 * ((float)1/JUEGO_FPS)));
                //Pegar con paleta 0 y 1
            }

            /*  //Frenado
            else if(moto_get_frenar(moto) && moto_get_vel > 0){
                moto_set_vel(moto,n_textos[SPEED] - 300/JUEGO_FPS);

                //LAS PALETAS DE FRENADO SON DIFERENTES
                //La paletas es la 2 y 3
            }
            */
            else if(frenar == true && n_textos[SPEED] > 0){ //Frenado
                n_textos[SPEED] -= 300/JUEGO_FPS;
                //ACA VA LAS ANIMACIONES DE FRENADO CON SU PALETA
                //La paleta es 2 y 3
            }
        }

        if(x_fondo < -2048) x_fondo = 640;
        else if(x_fondo > 640) x_fondo = -2048;

        
        imagen_pegar(cuadro, pasto_estirado, 0, 128);       
        imagen_pegar(cuadro, fondo2, (x_fondo * 0.75) + 320, 64);
        imagen_pegar(cuadro, fondo1, x_fondo + 320, 112);

        //esto sería la moto

        imagen_pegar(cuadro, cuadro_moto, x_moto - 30, 151);

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

        if(n_textos[TIME] == 0){
            size_t secs = 0;
            for(size_t i = 0;secs < 10; i++){
                //Mensaje de game over
                secs = i/JUEGO_FPS;
            }
            break;
        }    
    }


    // BEGIN código del alumno
    imagen_destruir(cuadro);
    imagen_destruir(fondo1);
    imagen_destruir(fondo2);
    imagen_destruir(cielo);
    imagen_destruir(cuadro_moto);

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
        imagen_destruir(teselas[i]);
    
    for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++)
        imagen_destruir(figuras[i]);
    
    imagen_destruir(ruta);

    imagen_destruir(pasto_estirado);

    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void numeros_a_pantalla(imagen_t *destino, imagen_t **origen,size_t i, int x, int y, size_t *text){
    char n_string[MAX_CADENA];
    sprintf(n_string,"%ld",text[i]);
    if(i == 1){
        imagen_t *segundos[10];
        for (size_t i = 0; i < 10; i++)
            segundos[i] = imagen_generar(ANCHO_TESELA, 2 * ALTO_TESELA, 0);
        for(size_t i = 0; i < 10; i++){
            imagen_pegar(segundos[i], origen[0x80 + (2 * i)], 0, 0);
            imagen_pegar(segundos[i], origen[0x81 + (2 * i)], 0, 8);
        }
        
        //for(size_t j = 0; n_string[j]; j++)
            //imagen_pegar_con_paleta(destino, segundos[(char)n_string[j]], x + (8 * j),y + 16,paleta_3[5]);

        for(size_t i = 0; i < 10; i++)
            imagen_destruir(segundos[i]);
        return;
    }
    for (size_t j = 0; n_string[j]; j++)
        imagen_pegar_con_paleta(destino, origen[(uint8_t)(n_string[j])], x + (8 * j) + (8 * strlen(textos[i].cadena)),y,paleta_3[5]);
}
    
