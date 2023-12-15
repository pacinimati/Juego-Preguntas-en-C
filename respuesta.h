#ifndef RESPUESTA_H_INCLUDED
#define RESPUESTA_H_INCLUDED

struct Respuesta;

typedef struct Respuesta * RespuestaPtr;

//TDA
int getNroRespuesta(RespuestaPtr e);
char * getRespuesta (RespuestaPtr e);
int getRespuestaCorrecta(RespuestaPtr e);
void setNroRespuesta(RespuestaPtr e, int numero);
void setRespuesta(RespuestaPtr e, const char *texto);
void setRespuestaCorrecta(RespuestaPtr e, int esCorrecta);
RespuestaPtr reservarEspacioRespuesta();
void liberarMemoriaRespuesta(RespuestaPtr respuesta);

#endif // RESPUESTA_H_INCLUDED
