#include "snake.h"
#include "sistema.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int Inicio, Fin;
int Orientacion, Pausa, Puntuacion;
double FactorRetraso;
COORD Snake[MAXLEN], Comida;

/**Checa si una posicion dada coincide con una de la serpiente, 1 - verdadero, 0 - falso**/
int ChecarSerpiente(COORD p) {
    int i;
    for (i = Inicio; i != Fin; i = (i + 1) % MAXLEN)
        if (Snake[i].X == p.X && Snake[i].Y == p.Y)
            return 1;
    return 0;
}

/**Checa si una posicion dada coincide con una pared, 1 - verdader, 0 - falso**/
int ChecarPared(COORD p) {
    if (p.X == 0 || p.X == 79 || p.Y == 2 || p.Y == 23)
        return 1;
    return 0;
}

/**Genera comida en una posicion aleatoria no ocupada**/
void GenerarComida() {
    do {
        Comida.X = Aleatorio(2, 77);
        Comida.Y = Aleatorio(4, 21);
    }
    while (ChecarSerpiente(Comida) == 1);
    ImprimeEnPosicion(Comida.X, Comida.Y, "O");
}

/**Añade un "bloque" mas a la serpiente**/
void DesplazarFrente(int x, int y) {
    Fin = (Fin + 1) % MAXLEN;
    Snake[Fin].X = x;
    Snake[Fin].Y = y;
    ImprimeEnPosicion(x, y, "#");
}

/**Borra la ultima posicion de la serpiente**/
void BorrarCola() {
    ImprimeEnPosicion(Snake[Inicio].X, Snake[Inicio].Y, " ");
    Inicio = (Inicio + 1) % MAXLEN;
}

/**Inicializa la serpiente en una posicion aleatoria con longitud dada y orientada a la derecha**/
void GenerarSerpiente(int largo) {
    Inicio = 0;
    Fin = -1;
    Orientacion = DERECHA;

    DesplazarFrente(Aleatorio(20, 60), Aleatorio(7, 17));
    while (largo > 0) {
        DesplazarFrente(Snake[Fin].X + 1, Snake[Fin].Y);
        largo--;
    }
}

/**Actualiza e imprime la puntuacion**/
void ActualizaPuntuacion(int nuevaPuntuacion) {
    Puntuacion = nuevaPuntuacion;
    EnteroEnPosicion(12, 0, Puntuacion);
}

/**Cambia la orientacion de la serpiente dependiendo la tecla presionada**/
void ReOrienta(int Tecla) {
    if ((Tecla == ARRIBA && Orientacion != ABAJO) //Checa que sea un movimiento valido
     || (Tecla == ABAJO && Orientacion != ARRIBA)
     || (Tecla == IZQUIERDA && Orientacion != DERECHA)
     || (Tecla == DERECHA && Orientacion != IZQUIERDA))
        Orientacion = Tecla;
    if (Tecla == ENTER) //Pone (1) o quita (-1) la pausa
    	Pausa *= -1;
}

/**Genera la proxima posicion de acuerdo a la tecla presionada**/
COORD SiguientePosicion(int Tecla) {
    COORD nuevo = Snake[Fin];
    ReOrienta(Tecla);

    switch (Orientacion) {
        case ARRIBA:    nuevo.Y--; break;
        case ABAJO:     nuevo.Y++; break;
        case IZQUIERDA: nuevo.X--; break;
        case DERECHA:   nuevo.X++;
    }

    return nuevo;
}

/**Mueve a la serpiente, retorna 1 si no es posible (Fin del Juego)**/
int Mover() {
    COORD nuevo = SiguientePosicion(PresionoTecla());

    if (Pausa != 1) {
		if (ChecarSerpiente(nuevo) || ChecarPared(nuevo))
	        return 1;
	    else {
	        DesplazarFrente(nuevo.X, nuevo.Y);
	        if (nuevo.X == Comida.X && nuevo.Y == Comida.Y) {
	        	FactorRetraso /= 1.0125; //Aumenta la velocidad del juego
	            GenerarComida(); //Genera nueva comida
	            ActualizaPuntuacion(Puntuacion + 100); //Incrementa la puntuacion
	        }
	        else
	            BorrarCola();
	    }
	}

    return 0;
}

/**Comienza una partida, retorna la puntuacion final**/
int NuevoJuego() {
    MostrarCursor(0);
    ImprimirPantalla("Data/InGame.bin");
    srand(time(0));

    GenerarSerpiente(4);
    GenerarComida();
    ActualizaPuntuacion(0);

    Pausa = -1;
    FactorRetraso = 100;
    while (Mover() != 1)
        Sleep(FactorRetraso);

    return Puntuacion;
}
