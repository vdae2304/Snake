#include "sistema.h"
#include "puntuacion.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct Usuario {
	int Puntuacion;
	char Nombre[51];
} usuario;

usuario Lista[11];

/**Carga las puntuaciones desde un archivo**/
void CargarPuntuaciones(char *archivo) {
    FILE *fp = fopen(archivo, "rb");
    fread(Lista, sizeof(usuario), 10, fp);
    fclose(fp);
}

/**Guarda de nuevo las puntuaciones en un archivo**/
void GuardarPuntuaciones(char *archivo) {
    FILE *fp = fopen(archivo, "wb");
    fwrite(Lista, sizeof(usuario), 10, fp);
    fclose(fp);
}

/**Reinicia la Tabla de Puntuaciones**/
void ReiniciarTabla() {
    int i;
    for (i = 0; i < 10; i++) {
        strcpy(Lista[i].Nombre, "Vacio");
        Lista[i].Puntuacion = 0;
    }
    GuardarPuntuaciones("Data/Score.bin");
}

/**Muestra la Tabla de Puntuaciones**/
void MostrarTabla() {
    int i;
    ImprimirPantalla("Data/Scoreboard.bin");
    for (i = 0; i < 10; i++) {
        ImprimeEnPosicion(4, i + 2, Lista[i].Nombre);
        EnteroEnPosicion(65, i + 2, Lista[i].Puntuacion);
    }
    MostrarCursor(0);
    if (getch() == DEL)
        ReiniciarTabla();
}

/**Compara las puntuaciones**/
int Comparar(const void *jugador1, const void *jugador2) {
	return ((usuario *)jugador2)->Puntuacion - ((usuario *)jugador1)->Puntuacion;
}

/**Lee el nombre y puntuacion del jugador y ordena la lista**/
void LeerNuevo(int puntuacionFinal) {
    scanf("%s", Lista[10].Nombre);
    Lista[10].Puntuacion = puntuacionFinal;
    qsort(Lista, 11, sizeof(usuario), Comparar);
}

/**Finaliza el juego y actualiza la tabla de puntuaciones**/
void FinDelJuego(int puntuacionFinal) {
    ImprimirPantalla("Data/GameOver.bin");
    EnteroEnPosicion(43, 14, puntuacionFinal);
    ImprimeEnPosicion(16, 17, "");
    MostrarCursor(1);

    CargarPuntuaciones("Data/Score.bin");
	LeerNuevo(puntuacionFinal);
	GuardarPuntuaciones("Data/Score.bin");
}
