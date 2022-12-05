#include <SDL2/SDL.h>
#include <stdbool.h>

#include "imagen.h"
#include "roms.h"
#include "fondo.h"
#include "paleta.h"
#include "figuras.h"
#include "moto.h"
#include "ruta.h"
#include "textos.h"

void destructor_masivo(imagen_t ** teselas, imagen_t ** figuras, imagen_t * ruta_completa, moto_t * moto, imagen_t * cuadro, imagen_t * cielo, imagen_t * pasto_estirado, imagen_t * fondo1, imagen_t * fondo2, imagen_t * top, imagen_t * score, imagen_t * time, imagen_t * goal, imagen_t * gameover, imagen_t * semaforo_sup);

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

    
    size_t n_textos[CANTIDAD_TEXTOS] = {[TOP] = 1000000,[TIME] = 75, [SCORE] = 0, [STAGE] = 1, [SPEED] = 0}; //en este arreglo de size_ts se guardan los valores asociados a los textos        

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

    imagen_t *top = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_TOP, mos_cuadro_top, mos_paleta_time);
    if(top == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto top\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir(fondo1);
        imagen_destruir(fondo2); 
        return 1;
    }
    imagen_t *score = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_SCORE, mos_cuadro_score, mos_paleta_time);
    if(score == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto score\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        return 1;
    }
    imagen_t *time = generar_mosaico(teselas, paleta_3, FILA_CUADROS, COLUMNA_TIME, mos_cuadro_time, mos_paleta_time);
    if (time == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto time\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        imagen_destruir(score);
        return 1;
    }
    imagen_t * goal = generar_mosaico(teselas, paleta_3, FILA_GG, COLUMNA_GOAL, mos_cuadro_goal, mos_paleta_goal);
    if (goal == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto goal\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        imagen_destruir(score);
        imagen_destruir(time);
        return 1;
    }
    imagen_t * gameover = generar_mosaico(teselas, paleta_3, FILA_GG, COLUMNA_GAMEOVER, mos_cuadro_gameover, mos_paleta_gameover);
    if (gameover == NULL){
        fprintf(stderr, "No se generó correctamente el cuadro de texto gameover\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        imagen_destruir_mas(score, time, goal);
    }
    
    imagen_t * semaforo_sup = imagen_generar(640 - 132 - 33, /*249*/ 48, 0);
    if (semaforo_sup == NULL){
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        imagen_destruir_mas(score, time, goal);
        imagen_destruir(gameover);
        return 1;   
    }
    imagen_pegar(semaforo_sup, figuras[VIGA_BANNER], 0, 0);
    imagen_pegar(semaforo_sup, figuras[VIGA_BANNER], 132 + 244 - 33, 0);
    imagen_pegar(semaforo_sup, figuras[BANNER_LARGADA], 132 - (33 / 2), 0);


    //Acá se crea la moto inicializado en sus respectivos valores
    moto_t *moto = moto_crear(0, 0, 0, false, false, false, false);
    if(moto == NULL){
        fprintf(stderr, "No se generó correctamente la memoria para la moto\n");
        roms_destruir(teselas, figuras, ruta_completa);
        imagen_destruir_mas(cuadro, cielo, pasto_estirado);
        imagen_destruir_mas(fondo1, fondo2, top);
        imagen_destruir_mas(score, time, goal);
        imagen_destruir(gameover);
        imagen_destruir(semaforo_sup);        
        return 1;
    }
    
    //Acá voy a crear las variables que necesito relativas a la posición de la ruta/figuras

    double x_fondo = 320, y = 0;
    size_t t = 0, del = 0, xi_semaforo = 35;
    bool chocamos = false;
    float secs = 0;
    
    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {
        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (del >= 4 * JUEGO_FPS){ 
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
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno       
        imagen_t *cuadro_moto = imagen_generar(60, 73, 0);
        if(cuadro_moto == NULL){
            fprintf(stderr, "cuadro_moto no se pudo generar\n");
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
            return 1;
        }

        imagen_pegar(cuadro, cielo, 0, 0);
        imagen_pegar(cuadro, pasto_estirado, 0, 128);       
        imagen_pegar(cuadro, fondo2, (x_fondo * 0.75) + 320, 64);
        imagen_pegar(cuadro, fondo1, x_fondo + 320, 112);
        
        if((n_textos[TIME] > 0 || moto_get_x(moto) < 4200) && del >= 4 * JUEGO_FPS && secs == 0)
            n_textos[TIME] = 75 - (t++ / JUEGO_FPS);

        //Posicion m_x    
        size_t x = 0;
        if((n_textos[TIME] > 0 || moto_get_x(moto) < 4200) && del >= 4 * JUEGO_FPS){                
            x = moto_get_x(moto);
            moto_set_x(moto, x + (1.0/JUEGO_FPS) * ((moto_get_vel(moto) * (1000.0/3600))));   
        }

        //Posicion m_y junto al movimiento de los fondos
        if(moto_get_izq(moto) && !chocamos){
            y += (6 * moto_get_pos(moto) + 3);
        } 
        else if(moto_get_der(moto) && !chocamos) {
            y += (6 * moto_get_pos(moto) - 3);      
        } 
        
        if(ruta[moto_get_x(moto)].radio_curva && !chocamos)
            y -= 2,5 * (moto_get_x(moto) - x) * ruta[moto_get_x(moto)].radio_curva; 

        if(y < -435 || y > 435)
            y = y < 0 ? -435 : 435;
        
        x_fondo -= ruta[moto_get_x(moto)].radio_curva;

        if(x_fondo < -2048 || x_fondo > 640)
            x_fondo = x_fondo < 0 ? 640 : -2048;
        
                      
        if(secs == 0){
            //Aceleración
            if((moto_get_acelerar(moto) || moto_get_vel(moto) < 80) && (!moto_get_frenar(moto) && del >= 4 * JUEGO_FPS)){
                moto_set_vel(moto,279 - (size_t)((279 - (n_textos[SPEED])) * exp(-0.224358 * ((float)1/JUEGO_FPS))));        }
            
            //Frenado
            else if(moto_get_frenar(moto) && moto_get_vel(moto) > 80){
                moto_set_vel(moto,(size_t)(n_textos[SPEED] - 300.0/JUEGO_FPS));
            }

            //Desaceleración
            else if(!moto_get_acelerar(moto) && !moto_get_frenar(moto) && moto_get_vel(moto) >= 80){ 
                moto_set_vel(moto,n_textos[SPEED] - 90/JUEGO_FPS);                   
            }
        }
        else 
            moto_set_vel(moto,0);
    
    
        if((!moto_get_izq(moto) && !moto_get_der(moto)) && moto_get_pos(moto) != 0){
            short aux = moto_get_pos(moto);
            moto_set_pos(moto,aux < 0 ? ++aux : --aux);   
        }
        
        if(chocamos){
            moto_set_pos(moto,0);
            moto_set_frenar(moto,false);
            moto_set_acelerar(moto,false);
        }

        pegar_moto(cuadro_moto, figuras, moto, t);


        //Morder la banquina + puntaje
        if (del >= 4 * JUEGO_FPS && (y > -215 || y < 215) && moto_get_x(moto) < 4200){
            if(moto_get_vel(moto) < 117)
                n_textos[SCORE] += 125 * (moto_get_x(moto) - x);

            else
                n_textos[SCORE] += (moto_get_x(moto) - x) * (3.13 * moto_get_vel(moto) - 240);
        }

        else if (moto_get_vel(moto) > 93)
            moto_set_vel(moto, moto_get_vel(moto) - 3);
        
        if(n_textos[TOP] < n_textos[SCORE])
            n_textos[TOP] = n_textos[SCORE];
      
        imagen_t *linea_ruta = imagen_generar(2* ANCHO_RUTA,1,0);
        if(linea_ruta == NULL){
            fprintf(stderr, "No se pudo generar la línea de la ruta :c\n");
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
            imagen_destruir(cuadro_moto);
            return 1;    
        }
        int d_c = 0;
        for(int i = 95; i >= 0; i--){
            imagen_pegar(linea_ruta, ruta_completa, 0, i - 111);
            int d_l = -y * (96 - i) / 96;
            int d = -1/0.11 * log((96 - i)/96);
            if (d < 0 || d > 60) 
                d = (d != 0) ? 60 : 0;
            if (x + i > 4260) continue;
            d_c += -1 * (ruta[x + d].radio_curva * exp(0.105 * i - 8.6));
            imagen_pegar_ruta_con_paleta(cuadro,linea_ruta,d_l + d_c - 346,223 - i,colores_ruta[((95 - x - i) /4) % 4]); //112 porque sacas las 16 filas de abajo    
            if (ruta[x + i].indice_figura != 9999){
                figs_t figura_a_pegar = figuras_en_ruta[ruta[x + i].indice_figura].figura;
                size_t alto_figura = figura_get_alto(figura_a_pegar) * ((96 - i)/ 96.0) + (5.0 * i)/96; 
                size_t ancho_figura = figura_get_ancho(figura_a_pegar) * ((float)alto_figura / figura_get_alto(figura_a_pegar));
                if(ancho_figura < 3) ancho_figura = 3;
                imagen_t * fig_escalada = imagen_escalar(figuras[figura_a_pegar], ancho_figura, alto_figura);
                if (fig_escalada == NULL){
                    fprintf(stderr, "no se pudo escalar la figura\n");
                    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
                    imagen_destruir(cuadro_moto);
                    imagen_destruir(linea_ruta);
                    return 1;
                }
                if (figuras_en_ruta[ruta[x + i].indice_figura].reflejar){
                    imagen_t * ref = imagen_reflejar(fig_escalada);
                    if (ref == NULL){
                        fprintf(stderr, "no se pudo reflejar la figura\n");
                        destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
                        imagen_destruir_mas(cuadro_moto, fig_escalada, linea_ruta);
                        return 1;
                    }
                    imagen_destruir(fig_escalada);
                    fig_escalada = ref;
                }   
                imagen_pegar_con_paleta(cuadro, fig_escalada, 162 + figuras_en_ruta[ruta[x + i].indice_figura].y * ((96 - i)/96.0) + figuras_en_ruta[ruta[x + i].indice_figura].y * (i/5000.0) + d_l + d_c - ancho_figura/2, 224 - i - alto_figura, paleta_4[figuras_en_ruta[ruta[x + i].indice_figura].paleta]);
                if(hay_choque(figura_a_pegar, ancho_figura, x, y))
                    chocamos = true;
                imagen_destruir(fig_escalada);
            }
        }
        
        imagen_destruir(linea_ruta);

        
        //Choques

        if (chocamos){
            moto_set_vel(moto, 0);
            moto_set_x(moto, x);
            if(y < -6)
                y += 3;
            else if (y > 6)
                y -= 3;
            else {
                y = 0;
                chocamos = false;
            }
        }

        n_textos[SPEED] = moto_get_vel(moto);
        
        //Creacion del semaforo y banners de llegada y salida
        if (del <= 6 * JUEGO_FPS || moto_get_x(moto) >= 4200 - 130){
            bool paleta_goal = false;
            int pos = moto_get_x(moto) - xi_semaforo;
            if (pos < 0 || pos > 4200 - 130){
                del++;
                pos *= (pos > 0) ? 1 : -1;
                if (pos > 3000){
                    pos = 4200 - moto_get_x(moto);
                    paleta_goal = true;
                }
                size_t alto_semaforo = figura_get_alto(SEMAFORO) * ((96 - pos)/ 96.0) + (5.0 * pos)/96, ancho_semaforo = figura_get_ancho(SEMAFORO) * (((float) alto_semaforo) / figura_get_alto(SEMAFORO));
                float escala = ((float)alto_semaforo) / figura_get_alto(SEMAFORO);
                imagen_t * semaforo_escalado = imagen_escalar(figuras[SEMAFORO], ancho_semaforo, alto_semaforo);
                if (semaforo_escalado == NULL){
                    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
                    imagen_destruir(cuadro_moto);
                    return 1;
                }
                imagen_t * sup_escalado = imagen_escalar(semaforo_sup, imagen_get_ancho(semaforo_sup) * escala, imagen_get_alto(semaforo_sup) * escala);
                if (sup_escalado == NULL){
                    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
                    imagen_destruir(cuadro_moto);
                    imagen_destruir(semaforo_escalado);
                    return 1;
                }
                size_t paleta_semaforo = 41 + del / JUEGO_FPS;
                if (paleta_semaforo > 44) paleta_semaforo = 44;
                imagen_pegar_con_paleta(cuadro, semaforo_escalado, imagen_get_ancho(cuadro)/2 - imagen_get_ancho(sup_escalado) / 2, imagen_get_alto(cuadro) - alto_semaforo - pos, paleta_4[paleta_semaforo]);
                imagen_pegar_con_paleta(cuadro, semaforo_escalado, imagen_get_ancho(cuadro)/2 + imagen_get_ancho(sup_escalado) / 2 - ancho_semaforo, imagen_get_alto(cuadro) - alto_semaforo - pos, paleta_4[paleta_semaforo]);
                imagen_pegar_con_paleta(cuadro, sup_escalado, imagen_get_ancho(cuadro) /2 - imagen_get_ancho(sup_escalado) /2, imagen_get_alto(cuadro) - (alto_semaforo + imagen_get_alto(sup_escalado)) - pos, paleta_4[(paleta_goal) ? 47 : 45]);
                imagen_destruir(semaforo_escalado);
                imagen_destruir(sup_escalado);
            }
        }
        
        //Esto sería la moto
        imagen_pegar(cuadro, cuadro_moto, 132, 151);

        //Impresión de textos:
        for(size_t i = 0; i < CANTIDAD_TEXTOS; i++){
            if(i < (CANTIDAD_TEXTOS - 1))
                numeros_a_pantalla(cuadro, teselas, i, 8 + textos[i].pos_x + (i < 3 ? 8 : 0),textos[i].pos_y + (i < 3 ? 0x8 : 0),n_textos,textos[i].paleta);
    
            for (size_t j = 0; textos[i].cadena[j] != '\0'; j++)
                imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)(textos[i].cadena[j])], textos[i].pos_x + (8 * j), textos[i].pos_y, paleta_3[textos[i].paleta]);
        }
        imagen_pegar(cuadro,top,textos[0].pos_x,textos[0].pos_y);
        imagen_pegar(cuadro,time,textos[1].pos_x,textos[1].pos_y);
        imagen_pegar(cuadro,score,textos[2].pos_x,textos[2].pos_y);


        //Victoria
        if(moto_get_x(moto) >= 4200){
            secs++;
            imagen_pegar(cuadro, goal, 320/2 - (4 * FILA_GG), 224/2);
        }

        //Derrota
        else if(n_textos[TIME] == 0){
            secs++;
            imagen_pegar(cuadro, gameover, 320/ 2 - (4 * FILA_GG), 224/ 2);
        }
        
        if (secs > 3 * JUEGO_FPS) break;

        // Procedemos a dibujar a pantalla completa:
        imagen_t *cuadro_escalado = imagen_escalar(cuadro, VENTANA_ANCHO, VENTANA_ALTO);
        if(cuadro_escalado == NULL){
            fprintf(stderr, "cuadro escalado falló\n");
            destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);
            imagen_destruir(cuadro_moto);
            return 1;   
        }

        imagen_a_textura(cuadro_escalado, canvas);

        imagen_destruir(cuadro_moto);
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

    destructor_masivo(teselas, figuras, ruta_completa, moto, cuadro, cielo, pasto_estirado, fondo1, fondo2, top, score, time, goal, gameover, semaforo_sup);

    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

void destructor_masivo(imagen_t ** teselas, imagen_t ** figuras, imagen_t * ruta_completa, moto_t * moto, imagen_t * cuadro, imagen_t * cielo, imagen_t * pasto_estirado, imagen_t * fondo1, imagen_t * fondo2, imagen_t * top, imagen_t * score, imagen_t * time, imagen_t * goal, imagen_t * gameover, imagen_t * semaforo_sup){
    roms_destruir(teselas, figuras, ruta_completa);
    moto_destruir(moto);
    imagen_destruir_mas(cuadro, cielo, pasto_estirado);
    imagen_destruir_mas(fondo1, fondo2, top);
    imagen_destruir_mas(score, time, goal);
    imagen_destruir(gameover);
    imagen_destruir(semaforo_sup);
}