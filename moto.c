#include "moto.h"
#include "paleta.h"
#include "textos.h"
#include "config.h"
#include "ruta.h"

#include <math.h>
#include <stdlib.h>

//Paleta 0 y 1 para cuando està andando
//Paleta 2 y 3 para cuando està frenando
struct moto{
    int ym;
    short pos;
    size_t vel, x;
    bool acelera, frena, mover_izq, mover_der, chocamos;
};
//
typedef struct{ //Se define aca porque es una estructura solo para el tda
    size_t x,y;
}stmoto_pos_t;

static const stmoto_pos_t pos[4] = {
    {12,0},     //Posiciones (x,y) de la moto 0 para pegarlas correctamente
    {12,3},     //Posiciones (x,y) de la moto 1 para pegarlas correctamente
    {7,10},     //Posiciones (x,y) de la moto 2 para pegarlas correctamente
    {0,19},     //Posiciones (x,y) de la moto 3 para pegarlas correctamente
};

//inv de rep: moto_t siempre tiene inicializados sus valores mientras m != NULL

static void moto_inicializar(moto_t * m, int y_i, short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i, bool choque_i){
    m->ym = y_i;
    m->pos = pos_i;
    m->x = x_i;
    m->vel = vel_i;
    m->acelera = ac_i;
    m->frena = fr_i;
    m->mover_izq = izq_i;
    m->mover_der = der_i;
    m->chocamos = choque_i;
}

moto_t *moto_crear(int y_i, short pos_i, size_t x_i, size_t vel_i, bool ac_i, bool fr_i, bool izq_i, bool der_i, bool choque_i){
    moto_t *m = malloc (sizeof(moto_t));
    if (m == NULL) return NULL;
    moto_inicializar(m, y_i, pos_i, x_i, vel_i, ac_i, fr_i, izq_i, der_i, choque_i);
    return m;
}

void moto_destruir (moto_t * m){
    free(m);
}

short moto_get_pos (moto_t * m){
    return m->pos;
}

size_t moto_get_x (moto_t * m){
    return m->x;
}

size_t moto_get_vel (moto_t * m){
    return m->vel;
}

int moto_get_y(moto_t * m){
    return m->ym;
}

bool moto_esta_acelerando (moto_t * m){
    return m->acelera;
}

bool moto_esta_frenando (moto_t * m){
    return m->frena;
}

bool moto_gira_der (moto_t * m){
    return m->mover_der;
}

bool moto_gira_izq (moto_t * m){
    return m->mover_izq;
}

bool moto_hay_choque(moto_t *m){
    return m->chocamos;
}

void moto_set_pos(moto_t * m, short p){
    m->pos = p;
}

void moto_set_x (moto_t * m, size_t x, size_t tiempo){
    if(tiempo > 0 || m->x <= META_MOTO)
        m->x = x;
}

void moto_set_vel (moto_t * m, size_t del, size_t secs, bool mordiendo_banquina){
    if(secs != 0){
        m->vel = 0;
        return;
    }

    if(mordiendo_banquina){
        m->vel -= 3;
        return;
    }

    //Aceleración
    if((m->acelera || m->vel < VELOCIDAD_MINIMA) && del >= 4 * JUEGO_FPS)
        m->vel = VELOCIDAD_MAXIMA - (size_t)((VELOCIDAD_MAXIMA - m->vel) * exp(-0.224358 * (1.0/JUEGO_FPS)));  //fórmula dada por el enunciado       

    //Frenado
    else if(m->frena && m->vel > VELOCIDAD_MINIMA){
        m->vel -= (size_t)(300.0/JUEGO_FPS); //fórmula dada por el enunciado
    }

    //Desaceleración
    else if(!m->acelera && !m->frena && m->vel >= VELOCIDAD_MINIMA){ 
        m->vel -= (size_t)(90.0/JUEGO_FPS); //fórmula dada por el enunciado          
    }
}

void moto_set_acelerar (moto_t * m, bool ac){
    m->acelera = ac;
}

void moto_set_frenar (moto_t * m, bool fr){
    m->frena = fr;
}

void moto_set_der (moto_t * m, bool d){
    m->mover_der = d;
}

void moto_set_izq (moto_t * m, bool i){
    m->mover_izq = i;
}

void moto_set_y(moto_t *moto, size_t x){
    if(moto->chocamos) return;
    
    if(moto->mover_izq){
        moto->ym += (6 * moto->pos + 3);
    } 

    else if(moto->mover_der) {
        moto->ym += (6 * moto->pos - 3);      
    } 

    if(ruta[(size_t)moto->x].radio_curva != 0){
        moto->ym -= 2.5 * (moto->x - x) * ruta[(size_t)moto->x].radio_curva; 
    }

    if(moto->ym < -IRSE_AL_PASTO || moto->ym > IRSE_AL_PASTO)
        moto->ym = (moto->ym < 0) ? -IRSE_AL_PASTO : IRSE_AL_PASTO;
}

bool moto_pegar(imagen_t **imagen, imagen_t *origen[], moto_t *moto, size_t t, bool choque){
    if (moto->pos < 0){
        imagen_t *reflejo = imagen_reflejar(origen[-1 * (moto->pos)]);
        if (reflejo == NULL) {
            return false;
        }
        imagen_pegar_con_paleta(*imagen, reflejo, pos[-1 * moto->pos].x, pos[-1 * moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frena) * 2)]);
        imagen_destruir(reflejo);
    }
    else{
        imagen_pegar_con_paleta(*imagen, origen[moto->pos], pos[moto->pos].x, pos[moto->pos].y, paleta_4[(!choque) * (t % 2 + (moto->frena) * 2)]);
    }
    return true;
}

void hay_choque_con_figuras (moto_t * m, size_t ancho, int d, size_t x){
    if (ruta[x + d].indice_figura == NO_HAY_FIGURAS_EN_RUTA) return;
    if (m->ym < figuras_en_ruta[ruta[x + d].indice_figura].y + ancho / 2 && m->ym > figuras_en_ruta[ruta[x + d].indice_figura].y - ancho / 2){
        m->chocamos = true;
    }
}

void manejo_de_choques(moto_t * m, size_t x, size_t *s){
    if(!m->chocamos) return;
    *s = *s + 1;
    moto_inicializar(m, 0, 0, x, 0, false, false, false, false, true);
    if ((*s) >= (DELAY_CHOQUE * JUEGO_FPS)){
        *s = 0;
        m->chocamos = false;
    }
}

