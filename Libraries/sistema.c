#include "sistema.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

/**Redirecciona el cursor a la posicion (x, y) e imprime la cadena dada**/
void ImprimeEnPosicion(int x, int y, char *texto) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf(texto);
}

/**Imprime un entero en la posicion (x, y)**/
void EnteroEnPosicion(int x, int y, int n) {
    ImprimeEnPosicion(x, y, "");
    printf("%d", n);
}

/**Muestra u oculta el cursor: 0 - ocultar, 1 - mostrar**/
void MostrarCursor(int visible) {
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 1;
   info.bVisible = visible;
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/**Imprime en pantalla el contenido guardado en "archivo"**/
void ImprimirPantalla(char *archivo) {
    FILE *fp = fopen(archivo, "rb");
    char i, s[81];
    system("cls");

    for (i = 0; i < 24; i++) {
        fread(s, sizeof(char), 81, fp);
        printf("%s\n", s);
    }
    fclose(fp);
}

/**Checa si se presiono una tecla, de ser asi retorna el valor, de lo contrario retorna 0**/
int PresionoTecla() {
    if (kbhit())
        return getch();
    return 0;
}

/**Retorna un numero aleatorio en el rango [a, b]**/
int Aleatorio(int a, int b) {
    return a + rand() % (b - a + 1);
}
