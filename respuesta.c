#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "respuesta.h"

struct Respuesta{

    int nroRespuesta;
    char respuesta[40];
  //  int nroRespuestaAsociada;
    int correcta;

};

//TDA
int getNroRespuesta(RespuestaPtr e) {
    return e->nroRespuesta;
};

char *getRespuesta(RespuestaPtr e) {
    return e->respuesta;
};

int getRespuestaCorrecta(RespuestaPtr e) {
    return e->correcta;
};

void setNroRespuesta(RespuestaPtr e, int numero) {
    e->nroRespuesta = numero;
}

void setRespuesta(RespuestaPtr e, const char *texto) {
    strcpy(e->respuesta, texto);
}

void setRespuestaCorrecta(RespuestaPtr e, int esCorrecta) {
    e->correcta = esCorrecta;
}

RespuestaPtr reservarEspacioRespuesta(){
    RespuestaPtr e = malloc(sizeof(struct Respuesta));
    return e;
};

void liberarMemoriaRespuesta(RespuestaPtr respuesta) {
    free(respuesta);
};


