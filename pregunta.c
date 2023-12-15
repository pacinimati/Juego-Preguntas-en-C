#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "pregunta.h"
#include "respuesta.h"
#include "jugador.h"

struct Pregunta{

    int nroPregunta;
    char pregunta[130];
    RespuestaPtr posibles[4];

};

//TDA

void liberarMemoriaPregunta(PreguntaPtr pregunta) {
    for (int i = 0; i < 4; i++) {
        liberarMemoriaRespuesta(pregunta->posibles[i]);
    }
    free(pregunta);
}

int getNroPregunta(PreguntaPtr e) {
    return e->nroPregunta;
};

char *getPregunta(PreguntaPtr e) {
    return e->pregunta;
};

char *getRespuestaPosible(PreguntaPtr e, int i ) {
    //char * respuesta = malloc(50);
   // strcpy(respuesta,getRespuesta(e->posibles[i]));
    return getRespuesta(e->posibles[i]);
};

PreguntaPtr reservarMemoriaPregunta(int cantPreguntas){

    PreguntaPtr e = malloc(sizeof(struct Pregunta));

    return e;
};


int getPreguntaCorrecta(PreguntaPtr e, int i){
    int a;
    a = getRespuestaCorrecta(e->posibles[i]);
    return a;
};

int getPreguntaNroRespuesta(PreguntaPtr e, int i){
    int a;
    a = getNroRespuesta(e->posibles[i]);
    return a;
};

///////////////////////////////////////////////////////

void cargarPreguntas(PreguntaPtr preguntas[]) {

    FILE *archivoPreguntas = fopen("preguntas.txt", "r");
    FILE *archivoRespuestas = fopen("respuestas.txt", "r");
    FILE *archivoRespuestasCorrectas = fopen("respuestas_correctas.txt", "r");

    if (archivoPreguntas == NULL || archivoRespuestas == NULL || archivoRespuestasCorrectas == NULL) {
        printf("Error al abrir los archivos.\n");
        exit(1);
    }

    for (int i = 0; i < CANTPREGUNTAS; i++) {
        preguntas[i] = malloc(sizeof(struct Pregunta));

        fgets(preguntas[i]->pregunta, sizeof(preguntas[i]->pregunta), archivoPreguntas);
        preguntas[i]->pregunta[strlen(preguntas[i]->pregunta) - 1] = '\0'; // Eliminar el salto de línea

        char respuestasLine[100];
        fgets(respuestasLine, sizeof(respuestasLine), archivoRespuestas);
        char *respuestaSeparada = strtok(respuestasLine, ",");
        for (int j = 0; j < 4; j++) {
            preguntas[i]->posibles[j] = reservarEspacioRespuesta();
            setRespuesta(preguntas[i]->posibles[j], respuestaSeparada);
            setNroRespuesta(preguntas[i]->posibles[j],  j + 1); // Asignar número de respuesta
            setRespuestaCorrecta(preguntas[i]->posibles[j],  0);
            respuestaSeparada = strtok(NULL, ",");
        }

        int respuestaCorrecta;
        fscanf(archivoRespuestasCorrectas, "%d", &respuestaCorrecta);
        setRespuestaCorrecta(preguntas[i]->posibles[respuestaCorrecta - 1],  1);
    }

    fclose(archivoPreguntas);
    fclose(archivoRespuestas);
    fclose(archivoRespuestasCorrectas);

}





