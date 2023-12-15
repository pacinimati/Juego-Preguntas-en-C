#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jugador.h"
#include "juego.h"
#include "time.h"
#include "respuesta.h"
#include "pregunta.h"


int main()
{

    //EN TEORIA EL TP CUMPLE CON ESTOS ITEMPS:
    //El TP cumple las consignas, calcula tiempos, usa memoria dinamica, usa TDA, y ABM de los datos.

    srand(time(0));
    printf("\n              !!!BIENVENIDO A QUIZ MANIA!!!\n\n");
    printf("REGLAS: TENDRAN QUE RESPONDER PREGUNTAS HASTA QUE TE EQUIVOQUES!!\n");
    printf("TIENES 15 SEGUNDOS, SI TARDAS MAS ESTAS FUERA!!\n");
    printf("CADA PREGUNTA CORRECTA VALE 100 PTS, SI TARDAS MENOS DE 10 SEGUNDOS SE SUMAN 50 EXTRAS!!\n\n");
    system("pause");
    system("cls");
    printf("         MENU PRINCIPAL\n\n");
    printf("OPCION 1: VER HISTORIAL JUGADORES\nOPCION 2: COMENZAR JUEGO\nELIGE QUE OPCION QUIERES: ");

    ///Contar lineas de Archivo Historico Jugadores->

    int cantLineas = contarLineasArchivoHistorico();

    ///Creo array de Jugadores->

    JuegoPtr j1  = cargarJuego(cantLineas);

    ///Cargo Jugadores desde archivo->

    cargarJugadoresDesdeArchivo(getVecDinamico(j1),cantLineas);

    ///Mini menu principal ->

    int opcion = ElegirOpcionMenu();

    if(opcion ==1){
        system("cls");
        //printf("Alias(s) - Dni(s) - Puntajes Maximos:\n\n");
        printf("\n           HISTORIAL JUGADORES: \n");
        mostrarJugadores(getVecDinamico(j1),cantLineas);
        printf("\n");
    }

    else{
        system("cls");
    }

    ///Si quiere eliminar un jugador(solo si vio ya los DNI, osea si antes habia seleccionado 1) sino como sabria a quien borrar) ->

    if(opcion ==1){

    printf("Deseas eliminar algun jugador? 1 = SI 2 = NO: ");
    int eliminar = ElegirSiBorrar();

    if (eliminar == 1){
        eliminarJugador(j1,cantLineas);
        guardarExistentes(j1, cantLineas);
       }

    if (eliminar == 2){
        system("cls");
       }
    }

    int opcionPartidaActual;

    if (opcion == 1){
        printf("DESEA JUGAR UNA PARTIDA: 1 = NO || 2 = SI\n");
        opcionPartidaActual = ElegirOpcionMenu();
    }

    if (opcion == 2){
        opcionPartidaActual = 2;  //Se pone automatico, ya que eligio jugar en el menu antes
    }

    ///Elige cantidad de jugadores y los agrega (si quiere jugar al juego) ->

    if (opcionPartidaActual == 2){

        system("cls");

        int numJugadores = ElegirNumJugadores();

        setListaJugadores(j1,crearVector(numJugadores));

        agregarJugadores(j1, numJugadores);

        /// Comenzar Juego, iniciar Preguntas y Respuestas ->

        comenzarJuego(j1, numJugadores);

        ///Liberar Memoria Preguntas

        liberarPreguntas(j1,numJugadores);

        ///Actualizar lista de Jugadores

        actualizarHistorico(getListaJugadores(j1),numJugadores,getVecDinamico(j1),cantLineas);
    }


    return 0;
}
