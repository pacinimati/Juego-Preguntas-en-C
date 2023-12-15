#include <stdio.h>
#include <stdlib.h>
#include "juego.h"
#include "jugador.h"
#include <string.h>
#include "respuesta.h"
#include "pregunta.h"
#include "puntos.h"
#include "time.h"


struct Juego{

    ///Jugadores:
    JugadorPtr *ListaJugadores; //array que almacena los jugadores en partida
    JugadorPtr *vecDinamico; //array para almacenar la lista existente (archivo.txt)
                             //le deberia cambiar el nombre xD

};

//TDA
JuegoPtr  getListaJugadores(JuegoPtr e){

    return e->ListaJugadores;
};

void  setListaJugadores(JuegoPtr e, JugadorPtr * l){

    e->ListaJugadores = l;
};

JuegoPtr  getVecDinamico(JuegoPtr e){

    return e->vecDinamico;
};

void  setVecDinamico(JuegoPtr e, JugadorPtr * l){

    e->vecDinamico = l;
};

///////////////////////////////////////////////////////


JuegoPtr cargarJuego(int t){

    //ACA CREO EL PTR JUEGO + CREO EL VECTOR QUE POSEE EL HISTORIAL DE JUGADORES
    JuegoPtr aux = malloc(sizeof(struct Juego));

    //creo los 2 array jugadores (el de partida, y el historico)
    //aux->ListaJugadores = crearVector(4);
    aux->vecDinamico = crearVector(t);


    return aux;

};

void agregarJugadores(JuegoPtr e, int t){

    for (int i = 0 ; i < t ; i ++){
        printf("Jugador %d: \n", i + 1);
        //JugadorPtr eAgregar = cargarJugadorTeclado();
        e->ListaJugadores[i] = cargarJugadorTeclado();
       // e[i]->puntos = malloc(sizeof(struct Puntos));
        //e[i]->puntos->actuales = 0;
     }
}

void hacerPreguntas(PreguntaPtr preguntas[], JuegoPtr juego, int numPreguntas, int a) {

    //Cambiar oden Preguntas
    for (int i = numPreguntas - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        PreguntaPtr temp = preguntas[i];
        preguntas[i] = preguntas[j];
        preguntas[j] = temp;
    }

    for (int i = 0; i < numPreguntas; i++) {
        PreguntaPtr pregunta = preguntas[i];
        //CargarPregunta
        printf("Pregunta: %s\n", getPregunta(pregunta));

        // Muestra las respuestas en el orden original
        for (int j = 0; j < 4; j++) {
            //char respuesta[40];
            //strcpy(respuesta,getRespuestaPosible(pregunta,j));
            printf("%d. %s\n", getPreguntaNroRespuesta(pregunta,j), getRespuestaPosible(pregunta,j));
        }

        ///TIEMPO

        double tiempo = 0;
        clock_t inicio = clock();

        int respuestaSeleccionada;
        printf("Ingrese el numero correspondiente a la opcion correcta: ");
        scanf("%d", &respuestaSeleccionada);

        while (respuestaSeleccionada < 1 || respuestaSeleccionada > 4) {
            printf("Elegi una opcion valida: ");
            scanf("%d", &respuestaSeleccionada);
        }

        ///FIN TIEMPO

        clock_t fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;

        //int respuesta = getPreguntaCorrecta(pregunta,respuestaSeleccionada - 1);

        ///SI RESPONDE EN TIEMPO

        if (tiempo<15){
            if (getPreguntaCorrecta(pregunta,respuestaSeleccionada - 1) == 1) {
            printf("\nRespuesta correcta!!\n");
            printf("Tardaste %.2f segundos\n",tiempo);
            setPuntosActualesJugador(juego->ListaJugadores[a],100 + getPuntosActualesJugador(juego->ListaJugadores[a]));

            //SI RESPONDE EN MENOS DE 10

            if (tiempo < 10) {
            setPuntosActualesJugador(juego->ListaJugadores[a],50 + getPuntosActualesJugador(juego->ListaJugadores[a]));
            }

            printf("Puntos actuales de %s: %d",getalias(juego->ListaJugadores[a]),getPuntosActualesJugador(juego->ListaJugadores[a]));
            sleep(2);
            system("cls");

        } else {
            system("cls");
            printf("\nRespuesta incorrecta, Ya tendras una mejor oportunidad!\n");
            printf("Tuviste %d puntos\n",getPuntosActualesJugador(juego->ListaJugadores[a]));
            sleep(1);
            break;
           }
        }

        ///SI NO RESPONDE EN TIEMPO

        else{
            system("cls");
            printf("\nTardaste demasiado\nEl limite era 15 y tardaste %f\nSe mas rapido la proxima\n", tiempo);
            printf("Tuviste %d puntos\n",getPuntosActualesJugador(juego->ListaJugadores[a]));
            sleep(5);
            break;
        }

    }

}


void comenzarJuego(JuegoPtr juego, int numJugadores) {

    int contador = 0;
    // Hacer las preguntas a cada jugador
    for (int i = 0; i < numJugadores; i++) {
        //Limpiar Pantalla
        system("cls");
        printf("Turno de %s\n", getalias(juego->ListaJugadores[i]));
        printf("Empieza en "); /// Temporizador 3 2 1
         for (int j = 3; j >= 1; j--) {
            printf("%d. ", j);
            sleep(1);
        }
        system("cls");
        setPreguntasJuego(juego->ListaJugadores[i]);
        hacerPreguntas(getPreguntasJuego(juego->ListaJugadores[i]),juego, CANTPREGUNTAS, i);  /// PREGUNTAS DEL JUEGO!!!
        printf("Fin del turno de %s\n", getalias(juego->ListaJugadores[i]));
        contador ++;
        sleep(2);
    }

    system("cls");

    ///CASO EMPATE:
    //LOS CHEQUEOS SON EN EL HIPOTETICO CASO DE QUE  HAYA 3 O MAS QUE TENGAN EL MISMO PUNTAJE
    //PARA QUE NO QUEDEN VARIOS CON IGUALDAD DE PUNTOS

    for (int a = 0 ; a < numJugadores; a ++){
        for (int i = 0 ; i < numJugadores - 1 ; i ++){
           for (int j = i + 1 ; j < numJugadores ; j ++){
             if (getPuntosActualesJugador(juego->ListaJugadores[i]) == getPuntosActualesJugador(juego->ListaJugadores[j])){
                 hacerDesempate(juego, i, j);
                 break;
            }
         }
       }
     }



    ///DEFINIR GANADOR

    int max = getPuntosActualesJugador(juego->ListaJugadores[0]);
    int userMax [40];
    strcpy(userMax, getalias(juego->ListaJugadores[0]));

    for (int i = 0 ; i < numJugadores ; i ++){
        if (getPuntosActualesJugador(juego->ListaJugadores[i])> max){
            max = getPuntosActualesJugador(juego->ListaJugadores[i]);
            strcpy(userMax, getalias(juego->ListaJugadores[i]));
        }
    }

    printf("!PUNTAJES FINALES!\n");

    for (int i = 0 ; i < numJugadores ; i ++){
        printf("%s: %d Puntos\n",getalias(juego->ListaJugadores[i]), getPuntosActualesJugador(juego->ListaJugadores[i]));
    }


    printf("\n\nGANADOR: %s\n\n\n", userMax);

 }

int contarLineasArchivoHistorico() {
    const char *nombreArchivo = "historicojugadores.txt";
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo historicojugadores.txt");
        exit(1);
    }

    int lineas = 0;
    char linea[100]; // Ajusta el tamaño según tus necesidades

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (linea[0] != '\n') { // Ignorar líneas vacías
        lineas++;
        }
    }

    fclose(archivo);
    return lineas;
}



void cargarJugadoresDesdeArchivo(JugadorPtr *v, int numJugadores) {
    FILE *archivo;

    archivo = fopen("historicojugadores.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo historicojugadores.txt\n");
        exit(1);
    }

    for (int pos = 0; pos < numJugadores; pos++) {
        char alias[20];
        int dni;
        int puntuacionMaxima;

        fscanf(archivo, "%[^,],%d,%d\n", alias, &dni, &puntuacionMaxima);

        JugadorPtr jugador = reservarMemoriaPuntosJugador();

        // Asignar memoria para la estructura 'puntos'

        setDni(jugador,dni);
        setNombre(jugador,alias);
        setPuntosMaximosJugador(jugador,puntuacionMaxima);
        setPuntosActualesJugador(jugador,0);

        v[pos] = jugador;
    }

    fclose(archivo);
}

void mostrarJugadoresArchivo(){
    FILE * archivoLeer;

    archivoLeer = fopen("historicojugadores.txt", "r");

    if (archivoLeer == NULL) {
        perror("Error al abrir el archivo historicojugadores.txt");
        exit(1);
    }

    char aux[40];

    while (fgets(aux, sizeof(aux), archivoLeer) != NULL) {
        // Verifica si la línea no está vacía
        if (strcmp(aux, "\n") != 0) {
            printf("------> %s", aux);
        }
    }

    printf("\n");

    fclose(archivoLeer);
    printf("\nAHORA VIENE LO DIVERTIDO! A SUPERAR ESTOS PUNTAJES!\n\n");
    system("pause");
    system("cls");

}

int ElegirOpcionMenu(){
    int a;
    scanf("%d", &a);
    while (a != 1 && a != 2){
        printf("Elegi una opcion valida (1 o 2)\n");
        scanf("%d", &a);
    }

    printf("\n");

    return a;
}

void actualizarHistorico(JugadorPtr *listaJugadores, int numPartidaJugadores, JugadorPtr *historicoJugadores, int numHistoricoJugadores) {
    FILE *archivoHistorico = fopen("historicojugadores.txt", "w");

    if (archivoHistorico == NULL) {
        printf("Error al abrir el archivo historicojugadores.txt");
        exit(1);
    }

    for (int i = 0; i < numHistoricoJugadores; i++) {
        int encontrado = 0;

        for (int j = 0; j < numPartidaJugadores; j++) {
            if (getDni(historicoJugadores[i]) == getDni(listaJugadores[j])) {
                encontrado = 1;

                if (getPuntosActualesJugador(listaJugadores[j]) > getPuntuacionMaximaJugador(historicoJugadores[i])) {
                    setPuntosMaximosJugador(historicoJugadores[i],getPuntosActualesJugador(listaJugadores[j]));
                }

                //Por si cambio el alias:
                setNombre(historicoJugadores[i],getalias(listaJugadores[j]));

                fprintf(archivoHistorico, "%s,%d,%d\n", getalias(historicoJugadores[i]), getDni(historicoJugadores[i]), getPuntuacionMaximaJugador(historicoJugadores[i]));

                break;
            }
        }

        if (!encontrado) {
            if(getDni(historicoJugadores[i])!= -1){
                fprintf(archivoHistorico, "%s,%d,%d\n", getalias(historicoJugadores[i]), getDni(historicoJugadores[i]), getPuntuacionMaximaJugador(historicoJugadores[i]));
            }

        }
    }

    // Ahora agregamos a los jugadores de la partida actual que no estén en el histórico
    for (int i = 0; i < numPartidaJugadores; i++) {
        int encontrado = 0;

        for (int j = 0; j < numHistoricoJugadores; j++) {
            if (getDni(listaJugadores[i]) == getDni(historicoJugadores[j])) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            fprintf(archivoHistorico, "%s,%d,%d\n", getalias(listaJugadores[i]), getDni(listaJugadores[i]), getPuntosActualesJugador(listaJugadores[i]));
        }
    }

    fclose(archivoHistorico);
}

void liberarPreguntas(JuegoPtr e, int cantJugadores) {
    for (int i = 0; i < cantJugadores; i++) {
        for (int j = 0; j < CANTPREGUNTAS; j++) {
            liberarMemoriaPregunta(getPreguntasJuegoIndex(e->ListaJugadores[i],j));
        }
    }
}

void eliminarJugador(JuegoPtr e, int cant) {
    int buscar;
    printf("\nQue jugador deseas eliminar de la lista historica(Ingresa el DNI): ");
    scanf("%d",&buscar);
    for (int i = 0 ; i < cant ; i ++){
        if (getDni(e->vecDinamico[i]) == buscar){
            e->vecDinamico[i] = cargarJugadorNulo();
            system("cls");
            return;
        }
    }

    printf("\nNo se encontro un jugador con ese DNI\n");
    system("pause");
    system("cls");
}

int ElegirSiBorrar(){
    int num;
    scanf("%d",&num);
    while (num != 1 && num != 2){
        printf("Elegi una opcion valida!\n");
        scanf("%d",&num);
    }

    return num;
}

void hacerDesempate(JuegoPtr juego, int i, int j){

    ///jugador 1

     int a = 10 + (rand() % (20 - 10 + 1));
     int b = 10 + (rand() % (20 - 10 + 1));
     int c = 10 + (rand() % (20 - 10 + 1));

     printf("HUBO UN EMPATE ENTRE %s y %s!!\n\n", getalias(juego->ListaJugadores[i]), getalias(juego->ListaJugadores[j]));
     printf("LA PREGUNTA DE DESEMPATE PARA %s ES!:\n",getalias(juego->ListaJugadores[i]));
     printf("CUANTO ES (%d + %d) * %d (inserte resultado): ",a,b,c);
     int resultado = (a + b) * c;
     int respuesta1;
     scanf("%d", &respuesta1);
     int diferencia1 = abs(resultado - respuesta1);

     ///jugador 2

     printf("\nLA PREGUNTA DE DESEMPATE PARA %s ES!:\n",getalias(juego->ListaJugadores[j]));
     a = 10 + (rand() % (20 - 10 + 1));
     b = 10 + (rand() % (20 - 10 + 1));
     c = 10 + (rand() % (20 - 10 + 1));
     printf("CUANTO ES (%d + %d) * %d (inserte resultado): ",a,b,c);
     int respuesta2;
     scanf("%d", &respuesta2);
     resultado = (a + b) * c;
     int diferencia2 = abs(resultado - respuesta2);
     system("cls");
     printf("%s ESTUVO a %d\n",getalias(juego->ListaJugadores[i]),diferencia1);
     printf("%s ESTUVO a %d\n\n",getalias(juego->ListaJugadores[j]),diferencia2);

    if (diferencia1 < diferencia2) {
        printf("%s ESTUVO MAS CERCA DEL RESULTADO CORRECTO! GANO EL DESEMPATE!\n",getalias(juego->ListaJugadores[i]));
        setPuntosActualesJugador(juego->ListaJugadores[i],100 + getPuntosActualesJugador(juego->ListaJugadores[i]));
        sleep(4);
        system("cls");
    }
    if (diferencia2 < diferencia1) {
        printf("%s ESTUVO MAS CERCA DEL RESULTADO CORRECTO! GANO EL DESEMPATE!\n",getalias(juego->ListaJugadores[j]));
        setPuntosActualesJugador(juego->ListaJugadores[j],100 + getPuntosActualesJugador(juego->ListaJugadores[j]));
        sleep(4);
        system("cls");
    }

    if(diferencia1 == diferencia2){
        printf("!!HUBO UN EMPATE ENTRE SUS RESPUESTAS, SUS PUNTAJES SE MANTIENEN!!!\n");
    }
}

void mostrarJugadores(JugadorPtr * e, int t){

    for(int i = 0 ; i < t ; i ++){
        printf("ALIAS: %s  DNI: %d  PUNTAJE MAXIMO %d\n",getalias(e[i]),getDni(e[i]),getPuntuacionMaximaJugador(e[i]));
    }
}

void guardarExistentes(JuegoPtr e, int t){
    FILE *archivoHistorico = fopen("historicojugadores.txt", "w");

    if (archivoHistorico == NULL) {
        printf("Error al abrir el archivo historicojugadores.txt");
        exit(1);
    }

    for (int i = 0 ; i < t ; i ++){
        if (getDni(e->vecDinamico[i]) != -1){
            fprintf(archivoHistorico, "%s,%d,%d\n", getalias(e->vecDinamico[i]), getDni(e->vecDinamico[i]), getPuntuacionMaximaJugador(e->vecDinamico[i]));
        }
    }

     fclose(archivoHistorico);
}
















