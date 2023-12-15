#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED
#include "jugador.h"

///CAMBIANDO A PUNTEROS : SI


struct Juego;

typedef struct Juego * JuegoPtr;


//TDA
JuegoPtr  getListaJugadores(JuegoPtr e);
void  setListaJugadores(JuegoPtr e, JugadorPtr * l);
void  setVecDinamico(JuegoPtr e, JugadorPtr * l);
JuegoPtr  getVecDinamico(JuegoPtr e);



JuegoPtr cargarJuego(int t); // int t es para el vecHistorico
void agregarJugadores(JuegoPtr e, int t);
void comenzarJuego(JuegoPtr juego, int numJugadores);
void hacerPreguntas(PreguntaPtr preguntas[], JuegoPtr juego, int numPreguntas, int a);
int contarLineasArchivoHistorico();
void cargarJugadoresDesdeArchivo(JugadorPtr *v, int numJugadores);
void mostrarJugadoresArchivo();//solo muestra contenido
void actualizarHistorico(JugadorPtr  *partidaJugadores, int numPartidaJugadores, JugadorPtr *historicoJugadores, int numHistoricoJugadores);
void liberarPreguntas(JuegoPtr e, int cantJugadores);
int ElegirOpcionMenu();
void eliminarJugador(JuegoPtr e, int cant);
int ElegirSiBorrar();
void hacerDesempate(JuegoPtr juego, int i, int j);

void mostrarJugadores(JugadorPtr * e, int t);//los muestro bien organizado
void guardarExistentes(JuegoPtr e, int t);





#endif // JUEGO_H_INCLUDED
