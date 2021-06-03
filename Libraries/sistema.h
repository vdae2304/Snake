#ifndef SISTEMA_H_INCLUDED
#define SISTEMA_H_INCLUDED

#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define SPACE 32
#define DEL 127
#define ESC 27

void ImprimeEnPosicion(int, int, char*);
void EnteroEnPosicion(int, int, int);

void MostrarCursor(int);
void ImprimirPantalla(char*);

int PresionoTecla();
int Aleatorio(int, int);

#endif // SISTEMA_H_INCLUDED
