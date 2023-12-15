#ifndef PREGUNTA_H_INCLUDED
#define PREGUNTA_H_INCLUDED
#include "respuesta.h"

struct Pregunta;

typedef struct Pregunta * PreguntaPtr;

//TDA
PreguntaPtr reservarMemoriaPregunta();
void cargarPreguntas(PreguntaPtr preguntas[]);
int getNroPregunta(PreguntaPtr e);
char *getPregunta(PreguntaPtr e);
char *getRespuestaPosible(PreguntaPtr e, int i );
int getPreguntaCorrecta(PreguntaPtr e, int i);
int getPreguntaNroRespuesta(PreguntaPtr e, int i);
void liberarMemoriaPregunta(PreguntaPtr pregunta);


#endif // PREGUNTA_H_INCLUDED
