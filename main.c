#include "Libraries/sistema.c"
#include "Libraries/snake.c"
#include "Libraries/puntuacion.c"
int main() {
    MostrarCursor(0);
    ImprimirPantalla("Data/Title.bin");
    while (1) {
        switch (PresionoTecla()) {
            case ESC:   ImprimeEnPosicion(0, 21, "");
                        return 0;
            case ENTER: FinDelJuego(NuevoJuego());
            case SPACE: CargarPuntuaciones("Data/Score.bin");
                        MostrarTabla();
                        ImprimirPantalla("Data/Title.bin");
        }
    }
    return 0;
}
