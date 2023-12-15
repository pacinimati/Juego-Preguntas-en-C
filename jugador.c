#include <stdio.h>
#include <stdlib.h>
#include "jugador.h"
#include "puntos.h"
#include "respuesta.h"
#include "pregunta.h"
#include <string.h>

//TDA

struct Jugador{

    int dni;
    char alias[10];
    PreguntaPtr preguntasJuego [CANTPREGUNTAS];
    PuntosPtr puntos;

};

int getDni(JugadorPtr e){
    return e->dni;
};

char * getalias(JugadorPtr e){
    return e->alias;
};

void setDni(JugadorPtr e, int dniNuevo){
    e->dni = dniNuevo;
};


void setNombre(JugadorPtr e, char nombre[40]){
    strcpy(e->alias, nombre);
};

void setPuntosActualesJugador(JugadorPtr e, int nuevoPuntaje){
    setPuntosActuales(e->puntos,nuevoPuntaje);
};

int getPuntosActualesJugador(JugadorPtr e){
   int puntos = getPuntosActuales(e->puntos);
   return puntos;
};

void  setPreguntasJuego(JugadorPtr e){
    cargarPreguntas(e->preguntasJuego);
};

JugadorPtr getPreguntasJuego(JugadorPtr e){
    return e->preguntasJuego;
};

JugadorPtr reservarMemoriaPuntosJugador(){
    JugadorPtr e = malloc(sizeof(struct Jugador));
    e->puntos = reservarMemoriaPuntos();
    return e;

};


 JugadorPtr *crearVector(int t) {
    JugadorPtr *pVector = (JugadorPtr *)malloc(t * sizeof(struct Jugador));
    return pVector;
};

JugadorPtr reservarMemoriaJugador(){
    JugadorPtr e = malloc(sizeof(struct Jugador));
    return e;
};

void setPuntosMaximosJugador(JugadorPtr e, int puntos){
    setPuntuacionMaxima(e->puntos,puntos);
};

int getPuntuacionMaximaJugador(JugadorPtr e){
    int puntos = getPuntosMaximo(e->puntos);
    return puntos;
};

JugadorPtr getPreguntasJuegoIndex(JugadorPtr e,int index){
    return e->preguntasJuego[index];
};

///////////////////////////////////////////////////////


JugadorPtr cargarJugadorTeclado(){

    JugadorPtr e = malloc(sizeof(struct Jugador));

    printf("Ingrese el alias:\n");
    fflush(stdin);
    gets(e->alias);
    while( strlen(e->alias) >10){
        printf("El alias es demasiado largo, intente denuevo:");
        printf("\nIngrese nuevamente: ");
        gets(e->alias);
    }

    printf("Ingrese el dni:\n");
    scanf("%d", &e->dni);
    while (e->dni < 0){
        printf("El DNI no puede ser menor a 0!, Ingrese Nuevamente: ");
        scanf("%d", &e->dni);
    }

    //Asigno espacio para puntos
    e->puntos = reservarMemoriaPuntos();
    setPuntosMaximosJugador(e,0);
    setPuntosActualesJugador(e,0);

    return e;
};


JugadorPtr cargarJugadorNulo(){

    JugadorPtr e = malloc(sizeof(struct Jugador));

    e->dni = -1;
    strcpy(e->alias, "VACIO");

    return e;
};


void cargarJugadoresNulos(JugadorPtr *e, int t){

    for ( int i = 0 ; i<t; i++){

        e[i] = cargarJugadorNulo();
    }
}


int ElegirNumJugadores() {
    char a[10];

    printf("Elegi el numero de Jugadores para la partida actual (2 o 4) ---> ");
    fflush(stdin);
    gets(a);

    while (strcmp(a, "2") != 0 && strcmp(a, "4") != 0) {
        printf("Elegi 2 o 4!!: \n");
        fflush(stdin);
        gets(a);
    }

    int num;
    if (strcmp(a, "4") == 0) {
        num = 4;
    } else {
        num = 2;
    }

    system("cls");
    return num;
}




