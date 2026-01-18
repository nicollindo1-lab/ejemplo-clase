#ifndef PUNTUACIONES_H
#define PUNTUACIONES_H

#define MAX_NOMBRE 30
#define ARCHIVO_PUNTUACIONES "puntuaciones.txt"

typedef struct
{
    char nombre[MAX_NOMBRE];
    int disparos;
    int impactos;
    int hundidos;
    int puntos;
} Puntuacion;

/* Funciones */
void InicializarPuntuacion(Puntuacion *p, const char *nombre);
void RegistrarDisparo(Puntuacion *p);
void RegistrarImpacto(Puntuacion *p);
void RegistrarHundido(Puntuacion *p);
void CalcularPuntos(Puntuacion *p, int gano);
void GuardarPuntuacion(Puntuacion p);
void MostrarPuntuaciones();

#endif