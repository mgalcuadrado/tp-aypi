#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

#include "imagen.h"
#include "roms.h"
#include "fondo.h"
#include "paleta.h"
#include "figuras.h"
#include "moto.h"
#include "ruta.h"
#include "textos.h"
#include "juego.h"

void destructor_masivo(imagen_t ** teselas, imagen_t ** figuras, imagen_t * ruta_completa, moto_t * moto, imagen_t * cuadro, imagen_t * cielo, imagen_t * pasto_estirado, imagen_t * fondo1, imagen_t * fondo2, imagen_t * cuadros_textos[CANTIDAD_CUADROS], imagen_t * semaforo_sup, imagen_t *cuadro_moto);

int main(void) {
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

    //inicio creación de imagenes
    imagen_t *teselas[CANTIDAD_TESELAS];
    imagen_t *figuras[CANTIDAD_FIGURAS];
    imagen_t *rutaza;

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);
        if (teselas[i] == NULL){
            fprintf(stderr, "No se generaron correctamente las teselas\n");
            for (size_t j = 0; j < i; j++)
                imagen_destruir(teselas[j]);
            return 1;
        }
    }

    for(figs_t i = 0; i < CANTIDAD_FIGURAS; i++){
        figuras[i] = imagen_generar(figura_get_ancho(i), figura_get_alto(i), 0);
        if (figuras[i] == NULL){
            fprintf(stderr, "No se generaron correctamente las figuras\n");
            for (size_t j = 0; j < CANTIDAD_TESELAS; j++)
                imagen_destruir(teselas[j]);
            for (size_t j = 0; j < i; j++)
                imagen_destruir(figuras[j]);
            return 1;
        }
    }

    rutaza = imagen_generar(ANCHO_RUTA, ALTO_RUTA, 0);
    if (rutaza == NULL){
        fprintf(stderr, "La ruta no se generó bien\n");
        roms_destruir(teselas, figuras, rutaza);
        return 1;
    }

    if (!roms_levantar(teselas, figuras, rutaza)){
        fprintf(stderr, "No se levantaron las roms correctamente\n");
        roms_destruir(teselas, figuras, rutaza);
        return 1;
    }

    imagen_t *ruta_reflejada = imagen_reflejar(rutaza);
    if (ruta_reflejada == NULL){
        fprintf(stderr, "No se reflejó correctamente la ruta\n");
        roms_destruir(teselas, figuras, rutaza);
        return 1;
    }

    imagen_t *ruta_completa = imagen_generar(2 * ANCHO_RUTA,ALTO_RUTA, 0);
    if(ruta_completa == NULL){
        fprintf(stderr, "no se pudo generar correctamente la ruta\n");
        roms_destruir(teselas, figuras, rutaza);
        imagen_destruir(ruta_reflejada);
        return 1;
    }

    imagen_pegar(ruta_completa,rutaza,0,0); 
    imagen_pegar(ruta_completa,ruta_reflejada,ANCHO_RUTA - 8,0);
    imagen_destruir(rutaza);
    imagen_destruir(ruta_reflejada);

    imagen_t *cuadro = imagen_generar(320, 224, 0);
    if(cuadro == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro principal\n");
        roms_destruir(teselas, figuras, ruta_completa);
        return 1;
    }
    imagen_t *cielo = imagen_generar(320, 128, 0xf);
    if(cielo == NULL){
        fprintf(stderr, "No se generó correctamente el cielo\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir(cuadro);
        return 1;
    }
    imagen_t *pasto = imagen_generar(1, 96, pixel12_crear(0, 13, 9));
    if(pasto == NULL){
        fprintf(stderr, "No se generó correctamente el pasto\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir(cuadro);
        imagen_destruir(cielo);
        return 1;
    }

    for(size_t i = 0; i < 10; i++)
        imagen_set_pixel(pasto, 0, i, colores_pasto[i]);

    imagen_t *pasto_estirado = imagen_escalar(pasto, 320, 96);
    imagen_destruir(pasto);
    if(pasto_estirado == NULL){
        fprintf(stderr, "No se generó correctamente el pasto estirado\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir(cuadro);
        imagen_destruir(cielo);
        return 1;
    }
    
    imagen_t *fondo1 = generar_mosaico(teselas, paleta_3, FONDO1_FILAS, FONDO1_COLUMNAS, fondo1_mosaico, fondo1_paleta);
    if(fondo1 == NULL){
        fprintf(stderr, "No se generó correctamente el fondo 1\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        return 1;
    }
    imagen_t *fondo2 = generar_mosaico(teselas, paleta_3, FONDO2_FILAS, FONDO2_COLUMNAS, fondo2_mosaico, fondo2_paleta);
    if(fondo2 == NULL){
        fprintf(stderr, "No se generó correctamente el fondo 2\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir(fondo1);
        return 1;
    }

    imagen_t *cuadros_textos[CANTIDAD_CUADROS];
    cuadros_textos[TOP] = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_TOP, mos_cuadro_top, mos_paleta_time);
    if(cuadros_textos[TOP] == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto top\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir(fondo1);
        imagen_destruir(fondo2); 
        return 1;
    }
    cuadros_textos[SCORE] = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_SCORE, mos_cuadro_score, mos_paleta_time);
    if(cuadros_textos[SCORE] == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto score\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        return 1;
    }
    cuadros_textos[TIME] = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_TIME, mos_cuadro_time, mos_paleta_time);
    if (cuadros_textos[TIME] == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto time\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        imagen_destruir(cuadros_textos[SCORE]);
        return 1;
    }
    cuadros_textos[GOAL] = generar_mosaico(teselas, paleta_3, FILA_GG, COLUMNA_GOAL, mos_cuadro_goal, mos_paleta_goal);
    if (cuadros_textos[GOAL] == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto goal\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        imagen_destruir(cuadros_textos[SCORE]);
        imagen_destruir(cuadros_textos[TIME]);
        return 1;
    }
    cuadros_textos[GAMEOVER] = generar_mosaico(teselas, paleta_3, FILA_GG, COLUMNA_GAMEOVER, mos_cuadro_gameover, mos_paleta_gameover);
    if (cuadros_textos[GAMEOVER] == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto gameover\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        imagen_destruir_mas(cuadros_textos[SCORE], cuadros_textos[TIME],cuadros_textos[GOAL]);
    }
    
    imagen_t * semaforo_sup = imagen_generar(640 - 132 - 33, 48, 0);
    if (semaforo_sup == NULL){
        fprintf(stderr, "No se pudo generar el semáforo\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        imagen_destruir_mas(cuadros_textos[SCORE], cuadros_textos[TIME],cuadros_textos[GOAL]);
        imagen_destruir(cuadros_textos[GAMEOVER]);
        return 1;   
    }
    imagen_pegar(semaforo_sup, figuras[VIGA_BANNER], 0, 0);
    imagen_pegar(semaforo_sup, figuras[VIGA_BANNER], 132 + 244 - 33, 0);
    imagen_pegar(semaforo_sup, figuras[BANNER_LARGADA], 132 - (33 / 2), 0);

    //Acá se crea la moto inicializado en sus respectivos valores
    moto_t *moto = moto_crear(0, 0, 0, 0, false, false, false, false, false);
    if(moto == NULL){
        fprintf(stderr, "No se generó correctamente la memoria para la moto\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, cuadros_textos[TOP]);
        imagen_destruir_mas(cuadros_textos[SCORE], cuadros_textos[TIME],cuadros_textos[GOAL]);
        imagen_destruir(cuadros_textos[GAMEOVER]);
        imagen_destruir(semaforo_sup);        
        return 1;
    }

    imagen_t *cuadro_moto = imagen_generar(60, 73, 0);
    if(cuadro_moto == NULL){
        fprintf(stderr, "cuadro_moto no se pudo generar\n");
        destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
        return 1;
    }

    juego_t * juego = juego_iniciar_parametros();
    if (juego == NULL){
        fprintf(stderr, "cuadro_moto no se pudo generar\n");
        destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
        return 1;
    }
    
    //Acá voy a crear las variables que necesito relativas a la posición de la ruta/figuras

    double x_fondo = 320;
    size_t t = 0, del = 0, xi_semaforo = 35, segundero_choques = 0;
    bool es_el_fin = false;
    float secs = 0;
    
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if ((del >= 4 * JUEGO_FPS) && !moto_hay_choque(moto)){ 
                if (event.type == SDL_KEYDOWN) {
                    // Se apretó una tecla
                    short aux = moto_get_pos(moto);
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            moto_set_acelerar(moto, true);     
                            break;
                        case SDLK_DOWN:
                            moto_set_frenar(moto, true);       
                            break;
                        case SDLK_RIGHT:
                            moto_set_der(moto, true);
                            moto_set_pos(moto, ++aux);           
                            if(aux > 2)
                                moto_set_pos(moto, 3);
                            break;
                        case SDLK_LEFT:
                            moto_set_izq(moto, true);
                            moto_set_pos(moto, --aux);           
                            if(aux < -2)
                                moto_set_pos(moto, -3);
                            break;
                    }
                }
                else if (event.type == SDL_KEYUP) {
                    // Se soltó una tecla
                    short aux = moto_get_pos(moto);  
                    switch(event.key.keysym.sym) {
                        case SDLK_UP:
                            moto_set_acelerar(moto, false);        
                            break;
                        case SDLK_DOWN:
                            moto_set_frenar(moto, false);          
                            break;
                        case SDLK_RIGHT:
                            moto_set_der(moto, false);             
                            moto_set_pos(moto, --aux);
                            break;
                        case SDLK_LEFT:
                            moto_set_izq(moto, false);            
                            moto_set_pos(moto, ++aux);
                            break;
                    }
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno       

        imagen_pegar(cuadro, cielo, 0, 0);
        imagen_pegar(cuadro, pasto_estirado, 0, 128);       
        imagen_pegar(cuadro, fondo2, (x_fondo * 0.75) + 320, 64);
        imagen_pegar(cuadro, fondo1, x_fondo + 320, 112);
        
        if (es_el_fin || moto_hay_choque(moto)){
            moto_set_izq(moto, false);
            moto_set_der(moto, false);
            moto_set_acelerar(moto, false);
            moto_set_frenar(moto, false);
        }

        if(del >= 4 * JUEGO_FPS && secs == 0)
            juego_set_tiempo(juego, moto,t++);

        //Posicion m_x    
        size_t x = 0;
        if(del >= 4 * JUEGO_FPS){
            x = moto_get_x(moto);
            moto_set_x(moto, x + (1.0/JUEGO_FPS) * ((moto_get_vel(moto)/3.6)), juego_get_tiempo(juego));   
        }

        //Posicion m_y 
        if (!moto_hay_choque(moto)){
            moto_set_y(moto, x);
        }

        //Fondos
        if(!moto_hay_choque(moto) && juego_get_tiempo(juego) != 0 && moto_get_x(moto) != x)
            x_fondo -= ruta[moto_get_x(moto)].radio_curva;

        if(x_fondo < -2048 || x_fondo > 640)
            x_fondo = x_fondo < 0 ? 640 : -2048;              

        moto_set_vel(moto, del, secs, false);
    
        if((!moto_gira_izq(moto) && !moto_gira_der(moto)) && moto_get_pos(moto) != 0 && !moto_hay_choque(moto)){
            short aux = moto_get_pos(moto);
            moto_set_pos(moto,aux < 0 ? ++aux : --aux);   
        }

        //Puntaje
        if (del >= 4 * JUEGO_FPS){
            juego_set_puntajes(juego, moto, x);
        }
        
        //ruta
        imagen_t *linea_ruta = imagen_generar(2* ANCHO_RUTA, 1, 0);
        if(linea_ruta == NULL){
            fprintf(stderr, "No se pudo generar la línea de la ruta :c\n");
            imagen_destruir(cuadro_moto);
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
            juego_finalizar(juego);
            return 1;    
        }
        int curva[ALTO_RUTA - 2 * FILAS_A_IGNORAR] = {0};
        int lateral[ALTO_RUTA - 2 * FILAS_A_IGNORAR] = {0};
        //el arreglo de figuras pegadas se encarga de guardar cuántas figuras se pegaron en cada posición d del arreglo
        for(int i = 0; i < ALTO_RUTA - 2 * FILAS_A_IGNORAR; i++){
            int d = -1/0.11 * log(((float)(ALTO_RUTA - 2.0 * FILAS_A_IGNORAR) - i)/(ALTO_RUTA - 2.0 * FILAS_A_IGNORAR));
            if (d < 0 || d > METROS_VISIBLES)
                d = (d > METROS_VISIBLES) ? METROS_VISIBLES : 0;
            if (x + d >= FIN_RUTA) continue;
            imagen_pegar(linea_ruta, ruta_completa, 0, i - 111);
            lateral[i] = - moto_get_y(moto) * ((float)(ALTO_RUTA - 2.0 * FILAS_A_IGNORAR) - i)/(ALTO_RUTA - 2.0 * FILAS_A_IGNORAR);;
            if (i > 0)
                curva[i] = curva[i - 1] + (ruta[x + d].radio_curva * exp(0.105 * i - 8.6)); //fórmula dada por el enunciado
            imagen_pegar_ruta_con_paleta(cuadro, linea_ruta, lateral[i] + curva[i] - 346, 223 - i, colores_ruta[(d + x / CANTIDAD_PALETAS_RUTA) % CANTIDAD_PALETAS_RUTA]);  
        }
        for (int d = 60; d >= 0; d--){
            if (ruta[x + d].indice_figura != NO_HAY_FIGURAS_EN_RUTA){
                size_t ancho_figura;
                int v = (ALTO_RUTA - 2 * FILAS_A_IGNORAR) - (ALTO_RUTA - 2 * FILAS_A_IGNORAR) * exp (-0.11 * d); //formula dada por el enunciado
                if (!pegar_figuras(&cuadro, figuras, ruta[x + d].indice_figura, v, &ancho_figura, lateral[v], curva[v])){
                    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
                    imagen_destruir(linea_ruta);
                    juego_finalizar(juego);
                    return 1;
                }
                hay_choque_con_figuras(moto, ancho_figura, d, x);
            }
        }
        imagen_destruir(linea_ruta);

        manejo_de_choques(moto, x, &segundero_choques);
        juego_set_speed(juego, moto);
        
        
        //Creación del semáforo y banners de llegada y salida
        if (del <= 6 * JUEGO_FPS || moto_get_x(moto) >= 4200 - 130){
            int pos = moto_get_x(moto) - xi_semaforo;
            if (pos < 0 || pos > 4200 - 130){
                if (!pegar_semaforo(del++, &pos, figuras, semaforo_sup, &cuadro, moto_get_y(moto), moto_get_x(moto))){
                    fprintf(stderr, "no se pudo pegar el semáforo\n");
                    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
                    juego_finalizar(juego);
                    return 1;
                }
            }
        }
        
        //Acá se pega la moto
        if (!moto_pegar(&cuadro_moto, figuras, moto, t, moto_hay_choque(moto))){
            fprintf(stderr, "No se pego correctamente la moto\n");
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
            juego_finalizar(juego);
            return 1;
        }
    
        imagen_pegar(cuadro, cuadro_moto, 132, 151);
        imagen_pintar(cuadro_moto, 0); //esto "limpia" el cuadro_moto

        //Impresión de textos:
        imprimir_textos(juego, &cuadro, teselas, cuadros_textos);

        //Victoria
        if(moto_get_x(moto) >= META_MOTO){
            secs++;
            es_el_fin = true;
            imagen_pegar(cuadro, cuadros_textos[GOAL], imagen_get_ancho(cuadro) / 2 - (4 * FILA_GG), imagen_get_alto(cuadro) / 2);
        }

        //Derrota
        else if(juego_get_tiempo(juego) == 0){
            secs++;
            es_el_fin = true;
            imagen_pegar(cuadro, cuadros_textos[GAMEOVER], imagen_get_ancho(cuadro) / 2 - (4 * FILA_GG), imagen_get_alto(cuadro) / 2);
        }
        
        if (secs > 3 * JUEGO_FPS) break;

        // Procedemos a dibujar a pantalla completa:
        imagen_t *cuadro_escalado = imagen_escalar(cuadro, VENTANA_ANCHO, VENTANA_ALTO);
        if(cuadro_escalado == NULL){
            fprintf(stderr, "cuadro escalado falló\n");
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
            juego_finalizar(juego);
            return 1;   
        }

        imagen_a_textura(cuadro_escalado, canvas);
    
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
    
    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, cuadros_textos, semaforo_sup, cuadro_moto);
    juego_finalizar(juego);

    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void destructor_masivo(imagen_t ** teselas, imagen_t ** figuras, imagen_t * ruta_completa, moto_t * moto, imagen_t * cuadro, imagen_t * cielo, imagen_t * pasto_estirado, imagen_t * fondo1, imagen_t * fondo2, imagen_t * cuadros_textos[CANTIDAD_CUADROS], imagen_t * semaforo_sup, imagen_t * cuadro_moto){
    roms_destruir(teselas, figuras, ruta_completa);
    moto_destruir(moto);
    imagen_destruir_mas(cuadro, cielo, pasto_estirado);
    imagen_destruir_mas(fondo1, fondo2, semaforo_sup);
    imagen_destruir_mas(cuadros_textos[TOP], cuadros_textos[SCORE], cuadros_textos[TIME]);
    imagen_destruir_mas(cuadros_textos[GOAL], cuadros_textos[GAMEOVER], cuadro_moto);
}