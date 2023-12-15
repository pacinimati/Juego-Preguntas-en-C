#include "puntos.h"

struct Puntos{
   // int codPuntuacion;
    int actuales;
    int puntuacionMaxima;

};


void setPuntosActuales(PuntosPtr e,int nuevosPuntos){
    e->actuales = nuevosPuntos;
}

int getPuntosActuales(PuntosPtr e){
    return e->actuales;
};

PuntosPtr reservarMemoriaPuntos(){
    PuntosPtr e = malloc(sizeof(struct Puntos));
    return e;
};

void setPuntuacionMaxima(PuntosPtr e,int nuevosPuntos){
    e->puntuacionMaxima = nuevosPuntos;
};

int getPuntosMaximo(PuntosPtr e){
    return e->puntuacionMaxima;
};

//void inicializarPuntos(PuntosPtr e){
 //   e->actuales = 0;
//};
