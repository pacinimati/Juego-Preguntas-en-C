#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED
#include "pregunta.h"
#include "respuesta.h"
#include "puntos.h"
#define CANTPREGUNTAS 80 ///Numero de preguntas actual

///CAMBIANDO A PUNTEROS : SI

struct Jugador;

typedef struct Jugador * JugadorPtr;

//TDA
int getDni(JugadorPtr e);
char * getalias(JugadorPtr e);
void setNombre(JugadorPtr e, char nombre[40]);
void setDni(JugadorPtr e, int dniNuevo);
void setPuntosActualesJugador(JugadorPtr e, int nuevoPuntaje);
int getPuntosActualesJugador(JugadorPtr e);
void  setPreguntasJuego(JugadorPtr e);
JugadorPtr getPreguntasJuego(JugadorPtr e);
JugadorPtr reservarMemoriaJugador();
JugadorPtr reservarMemoriaPuntosJugador();
void setPuntosMaximosJugador(JugadorPtr e, int puntos);
int getPuntuacionMaximaJugador(JugadorPtr e);
JugadorPtr getPreguntasJuegoIndex(JugadorPtr e,int index);



JugadorPtr cargarJugadorTeclado();
JugadorPtr cargarJugadorNulo();
void cargarJugadoresNulos(JugadorPtr *e, int t);
int ElegirNumJugadores();
JugadorPtr *crearVector(int t);




#endif // JUGADOR_H_INCLUDED
