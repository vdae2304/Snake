#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define MAXLEN 1500

int ChecarSerpiente(COORD);
int ChecarPared(COORD);

void GenerarComida();

void DesplazarFrente(int, int);
void BorrarCola();
void GenerarSerpiente(int);

void ActualizaPuntuacion(int);

void ReOrienta(int);
COORD SiguientePosicion(int);
int Mover();
int NuevoJuego();

#endif // SNAKE_H_INCLUDED
