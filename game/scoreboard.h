#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

class Scoreboard {
    public:
        // Estructura que representa cada una de las entradas en la tabla de
        // puntuaciones.
        struct Entry {
            char player[50];
            unsigned int score;

            Entry() {
                strcpy(this->player, "Vac\xa1o");
                this->score = 0;
            }

            Entry(char *player, unsigned int score) {
                strcpy(this->player, player);
                this->score = score;
            }

            Entry operator= (Entry &other) {
                strcpy(this->player, other.player);
                this->score = other.score;
                return *this;
            }
        };

        // Lee las 10 mejores puntuaciones desde un archivo.
        // Si no existe el archivo, devuelve las entradas por defecto.
        static Entry* loadScores() {
            FILE *load = fopen("data/scores.data", "rb");
            Entry *scores = new Entry[10];
            if (load) {
                fread(scores, sizeof(Entry), 10, load);
            }
            fclose(load);
            return scores;
        }

        // Guarda la lista de las 10 mejores puntuaciones.
        static void saveScores(Entry scores[]) {
            FILE *save = fopen("data/scores.data", "wb");
            fwrite(scores, sizeof(Entry), 10, save);
            fclose(save);
        }

        // Despliega la lista de las 10 mejores puntuaciones.
        static void displayScoreboard() {
            load_screen("screen/scoreboard.bin");

            Entry *scores = loadScores();
            for (int i = 0; i < 10; ++i) {
                print_at_position(10, 4 + i, scores[i].player, false);
                print_at_position(70, 4 + i, scores[i].score, false);
            }
            delete[] scores;

            while (get_key_pressed() != KEY_ENTER) {
                ;
            }
        }
};

#endif // SCOREBOARD_H_INCLUDED
