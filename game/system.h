#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

// Dimensiones de la pantalla.
const int HEIGHT = 25;
const int WIDTH = 90;

// Esquina superior izquierda y esquina inferior derecha del área de juego.
const int MIN_X = 1;
const int MIN_Y = 2;
const int MAX_X = WIDTH - 2;
const int MAX_Y = HEIGHT - 2;

// Teclas.
const int NO_KEY = 0;
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_UP = 72;
const int KEY_DOWN = 80;
const int KEY_ENTER = 13;

// Devuelve la tecla presionada (si se presionó alguna).
int get_key_pressed() {
    if (kbhit()) {
        return getch();
    }
    return NO_KEY;
}

// Imprime en la posición indicada.
template <class T>
void print_at_position(int x, int y, const T &value, bool show_cursor) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    CONSOLE_CURSOR_INFO info;

    coord.X = x;
    coord.Y = y;
    info.dwSize = 1;
    info.bVisible = show_cursor;

    SetConsoleCursorPosition(handle, coord);
    SetConsoleCursorInfo(handle, &info);
    cout << value;
}

// Ajusta el tamaño de la ventana.
void set_window_size() {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    SMALL_RECT rect;

    coord.X = WIDTH;
    coord.Y = HEIGHT;
    SetConsoleScreenBufferSize(handle, coord);

    rect.Left = 0;
    rect.Top = 0;
    rect.Bottom = HEIGHT - 1;
    rect.Right = WIDTH - 1;
    SetConsoleWindowInfo(handle, true, &rect);
}

// Imprime el contenido de la pantalla desde un archivo. Devuelve true si se
// pudo abrir el archivo y false en caso contrario.
bool load_screen(const char *file) {
    FILE *load = fopen(file, "rb");
    char screen[HEIGHT*WIDTH];
    memset(screen, 0, sizeof(screen));
    if (load) {
        fread(screen, sizeof(char), HEIGHT*WIDTH, load);
        print_at_position(0, 0, screen, false);
        fclose(load);
    }
    return false;
}

#endif // SYSTEM_H_INCLUDED
