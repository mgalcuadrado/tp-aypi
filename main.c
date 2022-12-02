#include <SDL2/SDL.h>
#include <stdbool.h>

#include "imagen.h"
#include "roms.h"
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
    KM,
    GOAL,
    GAMEOVER,
}texto_t;

typedef struct{
    const char cadena[MAX_CADENA];
    size_t pos_x, pos_y, paleta;
}sttexto_t;

const sttexto_t textos[CANTIDAD_TEXTOS] = {
    [TOP] = {"TOP", 0xd, 0x6, 8},
    [TIME] = {"TIME", 0x90, 0x6, 6},
    [SCORE] = {"SCORE", 0xc6, 0x6, 7},
    [STAGE] = {"STAGE", 0x14, 0x1c, 5},
    [SPEED] = {"SPEED", 0xc6, 0x1c, 6},
    [KM] = {"KM", 0x10e, 0x1c, 6},
};
/*
typedef struct{
    const uint16_t mosaico[][];
    const uint8_t paleta[][];
    size_t filas, columnas;
}stcuadro_t;
    
const stcuadro_t cuadro_textos[CANTIDAD_CUADROS] = {
    [TOP] = {mos_cuadro_top, mos_paleta_top, FILA_CUADROS, COLUMNA_TOP},
    [SCORE] = {mos_cuadro_score, mos_paleta_score, FILA_CUADROS, COLUMNA_SCORE},
    [TIME] = {mos_cuadro_time, mos_paleta_time, FILA_CUADROS, COLUMNA_TIME},
    [GOAL] = {mos_cuadro_goal, mos_paleta_goal, FILA_GOAL_GAMEOVER, COLUMNA_GOAL},
    [GAMEOVER] = {mos_cuadro_gameover, mos_paleta_gameover, FILA_GOAL_GAMEOVER, COLUMNA_GAMEOVER},
    };
*/

//Esta es una funcion auxiliar que imprime los diferentes tipos de numeros en la pantalla 
void numeros_a_pantalla(imagen_t *destino, imagen_t **origen, size_t i, int x, int y, size_t *text, size_t paleta);

bool roms_inicializar(imagen_t * teselas[], imagen_t * figuras[], imagen_t * ruta);


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
    size_t n_textos[CANTIDAD_TEXTOS] = {[TOP] = 1000000,[TIME] = 0, [SCORE] = 0, [STAGE] = 1, [SPEED] = 0}; //en este arreglo de size_ts se guardan los valores asociados a los textos        

       imagen_t *teselas[CANTIDAD_TESELAS];
    imagen_t *figuras[CANTIDAD_FIGURAS];
    imagen_t *ruta;

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);
        if (teselas[i] == NULL){
            fprintf(stderr, "generar teselas falló\n");
            for (size_t j = 0; j < i; j++)
                imagen_destruir(teselas[j]);
            return 1;
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
            return 1;
        }
    }

    ruta = imagen_generar(ANCHO_RUTA, ALTO_RUTA, 0);
    if (ruta == NULL){
        fprintf(stderr, "generar ruta falló\n");
        roms_destruir(teselas, figuras, ruta);
        return 1;
    }

    if (!roms_levantar(teselas, figuras, ruta)){
        fprintf(stderr, "al levantar se rompe todo\n");
        return 1;
    }

    imagen_t *rutaza = imagen_reflejar(ruta);
    if (rutaza == NULL){
        fprintf(stderr, "che falló en reflejar\n");
        roms_destruir(teselas, figuras, ruta); 
        return 1;
    }

    imagen_t *ruta_completa = imagen_generar(2 * ANCHO_RUTA,ALTO_RUTA, 0);
    if(ruta_completa == NULL) return 1;
    imagen_pegar(ruta_completa,ruta,0,0); 
    imagen_pegar(ruta_completa,rutaza,ANCHO_RUTA - 8,0);
    imagen_destruir(ruta);
    imagen_destruir(rutaza);

    imagen_guardar_ppm(ruta_completa, "ruta40.ppm", pixel12_a_rgb); //pruebas //mgalcuadrado

    moto_t *moto = moto_crear(0, 0, 0, false, false, false, false);
    //Acá se crea la moto inicializado en sus respectivos valores

    double x_moto = 162, x_fondo = 320, y = 0;
    size_t t = 0; 
    

    imagen_t *cuadro = imagen_generar(320, 224, 0);
    imagen_t *cielo = imagen_generar(320, 128, 0xf);
    imagen_t *pasto = imagen_generar(1, 96, pixel12_crear(0, 13, 9));

    for(size_t i = 0; i < 10; i++)
        imagen_set_pixel(pasto, 0, i, colores_pasto[i]);

    imagen_t *pasto_estirado = imagen_escalar(pasto, 320, 96);
    imagen_destruir(pasto);
    
    imagen_t *fondo1 = generar_mosaico(teselas, paleta_3, FONDO1_FILAS, FONDO1_COLUMNAS, fondo1_mosaico, fondo1_paleta);
    imagen_t *fondo2 = generar_mosaico(teselas, paleta_3, FONDO2_FILAS, FONDO2_COLUMNAS, fondo2_mosaico, fondo2_paleta);
    
    /*
    imagen_t *cuadros_de_texto[CANTIDAD_CUADROS]
    for(size_t i = 0; i < CANTIDAD_CUADROS; i++)
        cuadro_de_textos[i] = generar_mosaico(teselas,paleta_3,cuadro_textos[i].filas,cuadro_textos[i].columnas,cuadro_textos[i].mosaico,cuadro_textos[i].paleta);
    */

    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                short aux = moto_get_pos(moto);          
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        moto_set_acelerar(moto,true);     
                        break;
                    case SDLK_DOWN:
                        moto_set_frenar(moto,true);       
                        break;
                    case SDLK_RIGHT:
                        moto_set_der(moto,true);
                        moto_set_pos(moto,++aux);           
                        if(aux > 2)
                            moto_set_pos(moto,3);
                        break;
                    case SDLK_LEFT:
                        moto_set_izq(moto,true);
                        moto_set_pos(moto,--aux);           
                        if(aux < -2)
                            moto_set_pos(moto,-3);
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                short aux = moto_get_pos(moto);
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        moto_set_acelerar(moto,false);        
                        break;
                    case SDLK_DOWN:
                        moto_set_frenar(moto,false);          
                        break;
                    case SDLK_RIGHT:
                        moto_set_der(moto,false);             
                        moto_set_pos(moto,--aux);
                        break;
                    case SDLK_LEFT:
                        moto_set_izq(moto,false);            
                        moto_set_pos(moto,++aux);
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno       
        imagen_t *cuadro_moto = imagen_generar(60, 73, 0);

        imagen_pegar(cuadro, cielo, 0, 0);
        imagen_pegar(cuadro, pasto_estirado, 0, 128);       
        imagen_pegar(cuadro, fondo2, (x_fondo * 0.75) + 320, 64);
        imagen_pegar(cuadro, fondo1, x_fondo + 320, 112);
        
        n_textos[TIME] = 75 - (t++ / JUEGO_FPS);
        
        //impresión de textos:
        for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
            if(i < (CANTIDAD_TEXTOS - 1))
                numeros_a_pantalla(cuadro, teselas, i, 8 + textos[i].pos_x + (i < 3 ? 8 : 0),textos[i].pos_y + (i < 3 ? 0x8 : 0),n_textos,textos[i].paleta);
            if(i < 3){
                //imagen_pegar(cuadro,,textos[i].pos_x,textos[i].pos_y);
                continue;
            }
            for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
                imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[textos[i].paleta]);

        }
        
        //Posicion m_y junto al movimiento de los fondos
        if(moto_get_izq(moto)){
            x_fondo += 10;
            y -= (6 * moto_get_pos(moto) + 3);
        } 
        else if(moto_get_der(moto)) {
            x_fondo -= 10;
            y -= (6 * moto_get_pos(moto) - 3);
        } 

        if(y < -435 || y > 435)
            y = y < 0 ? -435 : 435;

        if(x_fondo < -2048 || x_fondo > 640)
            x_fondo = x_fondo < 0 ? 640 : -2048;
        
                
        //Posicion m_x                    
        size_t x = moto_get_x(moto);
        moto_set_x(moto, x + (1.0/JUEGO_FPS) * ((moto_get_vel(moto) * (1000.0/3600))));   

        
        //Aceleración
        if((moto_get_acelerar(moto) || moto_get_vel(moto) < 80) && !moto_get_frenar(moto)){
            moto_set_vel(moto,279 - (size_t)((279 - (n_textos[SPEED])) * exp(-0.224358 * ((float)1/JUEGO_FPS))));        }
        
        //Frenado
        else if(moto_get_frenar(moto) && moto_get_vel(moto) > 80){
            moto_set_vel(moto,(size_t)(n_textos[SPEED] - 300.0/JUEGO_FPS));
        }

        //Desaceleración
        else if(!moto_get_acelerar(moto) && !moto_get_frenar(moto) && moto_get_vel(moto) >= 80){ 
            moto_set_vel(moto,n_textos[SPEED] - 90/JUEGO_FPS);                   
        }
        
        if((!moto_get_izq(moto) && !moto_get_der(moto)) && moto_get_pos(moto) != 0){
            short aux = moto_get_pos(moto);
            moto_set_pos(moto,aux < 0 ? ++aux : --aux);   
        }
        
        pegar_moto(cuadro_moto, figuras, moto, t);

        n_textos[SPEED] = moto_get_vel(moto);

        /*  //Choques
        
        */

        //Morder la banquina + puntaje
        if(y > -215 || y < 215){
            if(moto_get_vel(moto) < 117)
                n_textos[SCORE] += 125 * (moto_get_x(moto) - x);

            else
                n_textos[SCORE] += (moto_get_x(moto) - x) * (3.13 * moto_get_vel(moto) - 240);
        }

        //Victoria
        if(n_textos[TOP] < n_textos[SCORE])
            n_textos[TOP] = n_textos[SCORE];
        
        if(moto_get_x(moto) == 4200){
            size_t secs = 0;
            for(size_t i = 0;secs < 10; i++){
                //Mensaje de win
                secs = i/JUEGO_FPS;
            }
            break; //Podria hacer una funcion auxiliar para pegar los mensajes y hacer esperar unos
                   //5 segundos para que se vean los msg 
        }

        //Derrota
        if(n_textos[TIME] == 0){
            size_t secs = 0;
            for(size_t i = 0;secs < 10; i++){
                //Mensaje de game over
                secs = i/JUEGO_FPS;
            }
            break;
        } 

        //Acá se pega la ruta
        //lo que hay que hacer es intercalar cada cierta cantidad de metros la paleta para que queden bien las rayas blancas y negras, nos conviene hacerlo al mismo tiempo que las curvamos y eso
        //paleta
        imagen_pegar_con_paleta(cuadro,ruta_completa,(y - 346),128 - 16,colores_ruta[3]);
        //A ver, la ruta esta pero hay que arreglarlo
    
        
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
        imagen_destruir(cuadro_moto);

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
    imagen_destruir(pasto_estirado);

    moto_destruir(moto);

    roms_destruir(teselas, figuras, ruta);

    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void numeros_a_pantalla(imagen_t *destino, imagen_t **origen, size_t i, int x, int y, size_t *text, size_t paleta){
    char n_string[MAX_CADENA];
    sprintf(n_string,"%ld",text[i]);
    if(i == 1){
        for(size_t j = 0; j < 2; j++){ //
            imagen_pegar_con_paleta(destino, origen[0x80 + (j == 0? 2 * (text[i]/10) : 0) + (j == 1 ? (2 * (text[i] - (10 * (text[i]/10)))) : 0)], x + (8 * j),y + 16,paleta_3[5]);
            imagen_pegar_con_paleta(destino, origen[0x81 + (j == 0? 2 * (text[i]/10) : 0) + (j == 1 ? (2 * (text[i] - (10 * (text[i]/10)))) : 0)], x + (8 * j),y + 24,paleta_3[5]);
        } 
        return;
    }
    for (size_t j = 0; n_string[j]; j++)
        imagen_pegar_con_paleta(destino, origen[(uint8_t)(n_string[j])], x + (8 * j) + (8 * strlen(textos[i].cadena)) + (i == 4 && text[i] < 100 ? (text[i] < 0 ? 16 : 8) : 0),y,paleta_3[paleta + (i == 3 ? 1 : 0)]);
}
