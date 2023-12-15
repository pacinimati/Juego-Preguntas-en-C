#ifndef PUNTOS_H_INCLUDED
#define PUNTOS_H_INCLUDED

struct Puntos;

typedef struct Puntos * PuntosPtr;

//TDA
void setPuntosActuales(PuntosPtr e,int nuevosPuntos);
int getPuntosActuales(PuntosPtr e);
PuntosPtr reservarMemoriaPuntos();
void setPuntuacionMaxima(PuntosPtr e,int nuevosPuntos);
int getPuntosMaximo(PuntosPtr e);
//void inicializarPuntos(PuntosPtr e);





#endif // PUNTOS_H_INCLUDED
