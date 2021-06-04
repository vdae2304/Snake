#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Game {
    public:
        // Imprime la pantalla de título y espera a que el jugador pulse
        // ENTER.
        static void displayTitleScreen() {
            load_screen("screen/title.bin");
            while (get_key_pressed() != KEY_ENTER) {
                ;
            }
        }

        // Crea una nueva partida y devuelve la puntuación obtenida.
        static int newGame() {
            load_screen("screen/in-game.bin");

            unsigned int score = 0;
            bool game_in_pause = false;
            bool game_over = false;

            Snake snake(WIDTH/2, HEIGHT/2, KEY_RIGHT);
            Food food(snake, time(0));

            while (!game_over) {
                int key_pressed = get_key_pressed();

                // Si el jugador presionó Enter, pausa el juego o quita la
                // pausa.
                if (key_pressed == KEY_ENTER) {
                    if (game_in_pause) {
                        print_at_position(WIDTH - 6, 0, "     ", false);
                        game_in_pause = false;
                    }
                    else {
                        print_at_position(WIDTH - 6, 0, "Pausa", false);
                        game_in_pause = true;
                    }
                }

                // Si el juego está en pausa no hace nada.
                if (game_in_pause) {
                    continue;
                }

                // Mueve la serpiente según la tecla presionada.
                // Si se realizó algún movimiento inválido, finaliza el juego.
                int new_x, new_y;
                if (snake.move(key_pressed, new_x, new_y)) {
                    snake.push_head(new_x, new_y);
                    if (food.ate_food(snake)) {
                        score += 100;
                        print_at_position(9, 0, score, false);
                        food.gen_new_food(snake);
                    }
                    else {
                        snake.pop_tail();
                    }
                    Sleep(100);
                }
                else {
                    game_over = true;
                }
            }

            return score;
        }

        // Despliega la pantalla de fin de juego y guarda la puntuación
        // obtenida por el jugador.
        static void displayGameOver(unsigned int new_score) {
            load_screen("screen/game-over.bin");
            print_at_position(29, 13, new_score, false);
            print_at_position(13, 18, "", true);

            Scoreboard::Entry *scores = Scoreboard::loadScores();
            Scoreboard::Entry new_entry("", new_score);
            cin.getline(new_entry.player, 50);

            for (int i = 0; i < 10; ++i) {
                if (scores[i].score < new_entry.score) {
                    for (int j = 9; j > i; --j) {
                        scores[j] = scores[j - 1];
                    }
                    scores[i] = new_entry;
                    break;
                }
            }

            Scoreboard::saveScores(scores);
            delete[] scores;
        }
};

#endif // GAME_H_INCLUDED
