#include "figuras.h"
#include "ruta.h"
#include "paleta.h"

#include <stddef.h>


struct pos_figuras{
    size_t inicio, ancho, alto;
};

pos_figuras_t arr_pos_figuras[CANTIDAD_FIGURAS] = {
    [MOTO_1] = {532, 36, 73},
    [MOTO_2] = {5670, 36, 70},
    [MOTO_3] = {11284, 46, 63},
    [MOTO_4] = {17215, 60, 54},
    [ARBOL] = {50116, 46, 188},
    [CARTEL] = {37390, 96, 112},
    [ROCA] = {69464, 136, 76},
    [BELL] = {82922, 63, 146},
    [FORUM] = {89102, 118, 114},
    [DELFIN] = {119280, 144, 110},
    [SEMAFORO] = {108724, 66, 201},
    [BANNER_LARGADA] = {114518, 244, 48},
    [VIGA_BANNER] = {127098, 198, 48},
};

size_t figura_get_inicio (figs_t fig){
    return arr_pos_figuras[fig].inicio;
}

size_t figura_get_ancho (figs_t fig){
    return arr_pos_figuras[fig].ancho;
}

size_t figura_get_alto (figs_t fig){
    return arr_pos_figuras[fig].alto;
}

bool hay_choque (size_t ancho_escalado , int d, size_t x, size_t y){
        if (ruta[x + d].indice_figura == 9999) return false;
        if (y < figuras_en_ruta[ruta[x + d].indice_figura].y + ancho_escalado && y > figuras_en_ruta[ruta[x + d].indice_figura].y - ancho_escalado)
            return true;
    return false;
}

bool pegar_figuras(imagen_t ** destino, imagen_t * figuras[], size_t indice, size_t i, size_t *ancho_figura, int dlat, int dcur){
    figs_t figura_a_pegar = figuras_en_ruta[indice].figura;
    size_t alto_figura = figura_get_alto(figura_a_pegar) * ((96 - i)/ 96.0) + (5.0 * i)/96; 
    *ancho_figura = figura_get_ancho(figura_a_pegar) * ((float)alto_figura / figura_get_alto(figura_a_pegar));
    if(*ancho_figura < 3) *ancho_figura = 3;
    imagen_t *fig_escalada = imagen_escalar(figuras[figura_a_pegar], *ancho_figura, alto_figura);
    if (fig_escalada == NULL){
        fprintf(stderr, "no se pudo escalar la figura\n");
        return false;
    }
    if (figuras_en_ruta[indice].reflejar){
        imagen_t *ref = imagen_reflejar(fig_escalada);
        imagen_destruir(fig_escalada);
        if (ref == NULL){
            fprintf(stderr, "no se pudo reflejar la figura\n");
            return false;
        }
        fig_escalada = ref;
    }   
 imagen_pegar_con_paleta(*destino, fig_escalada, 162 + figuras_en_ruta[indice].y * ((96 - i)/96.0) + figuras_en_ruta[indice].y * (i/5000.0) + dlat + dcur - *ancho_figura/2, 224 - i - alto_figura, paleta_4[figuras_en_ruta[indice].paleta]);
 imagen_destruir(fig_escalada);
    return true;
}


bool pegar_semaforo(size_t del, int *pos, imagen_t * figuras[], imagen_t * sup, imagen_t **destino, int y, size_t x){
    bool paleta_goal = false;
    *pos *= (*pos > 0) ? 1 : -1;
    if (*pos > 3000){
        *pos = 4200 - x;
        paleta_goal = true;
    }
    size_t alto_semaforo = figura_get_alto(SEMAFORO) * ((96 - *pos)/ 96.0) + (5.0 * (*pos))/96, ancho_semaforo = figura_get_ancho(SEMAFORO) * (((float) alto_semaforo) / figura_get_alto(SEMAFORO));
    float escala = ((float)alto_semaforo) / figura_get_alto(SEMAFORO);
    imagen_t *semaforo_escalado = imagen_escalar(figuras[SEMAFORO], ancho_semaforo, alto_semaforo);
    if (semaforo_escalado == NULL){
        return false;
    }
    imagen_t *sup_escalado = imagen_escalar(sup, imagen_get_ancho(sup) * escala, imagen_get_alto(sup) * escala);
    if (sup_escalado == NULL){
        imagen_destruir(semaforo_escalado);
        return false;
    }
    size_t paleta_semaforo = INICIO_PALETA_SEMAFORO + del / JUEGO_FPS;
    if (paleta_semaforo > FIN_PALETA_SEMAFORO) paleta_semaforo = FIN_PALETA_SEMAFORO;
    imagen_pegar_con_paleta(*destino, semaforo_escalado, 162 - imagen_get_ancho(sup_escalado) / 2 - y, 224 - alto_semaforo - *pos, paleta_4[paleta_semaforo]);
    imagen_pegar_con_paleta(*destino, semaforo_escalado, 162 + imagen_get_ancho(sup_escalado) / 2 - ancho_semaforo - y, 224 - alto_semaforo - *pos, paleta_4[paleta_semaforo]);
    imagen_pegar_con_paleta(*destino, sup_escalado, 162 - imagen_get_ancho(sup_escalado) /2 - y, 224 - (alto_semaforo + imagen_get_alto(sup_escalado)) - *pos, paleta_4[(paleta_goal) ? PALETA_GOAL : PALETA_START]);
    imagen_destruir(semaforo_escalado);
    imagen_destruir(sup_escalado);
    return true;
}