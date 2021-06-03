#ifndef PUNTUACION_H_INCLUDED
#define PUNTUACION_H_INCLUDED

void CargarPuntuaciones(char*);
void GuardarPuntuaciones(char*);

void ReiniciarTabla();
void MostrarTabla();

int Comparar(const void*, const void*);
void LeerNuevo(int);
void FinDelJuego(int);

#endif // PUNTUACION_H_INCLUDED
