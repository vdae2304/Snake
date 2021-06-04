#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

class AI {
    protected:
        struct path {
            int x, y;

            path(int x, int y) {
                this->x = x;
                this->y = y;
            }
        };

    public:
        // Construye una matriz con los elementos en la pantalla de juego.
        static void getMatrixFromScreen(
            char screen[WIDTH][HEIGHT], const Snake &snake, const Food &food
        ) {
            memset(screen, ' ', HEIGHT*WIDTH*sizeof(char));
            for (Snake::node *it = snake.tail; it != nullptr; it = it->next) {
                screen[it->x][it->y] = '#';
            }
            screen[food.x][food.y] = 'O';
        }

        // Calcula el camino más corto desde la cabeza de la serpiente hasta la
        // comida. Devuelve la dirección que se debe tomar.
        static int getShortestPathToFood(const Snake &snake, const Food &food) {
            // Realiza una búsqueda en amplitud desde la comida hasta la cabeza
            // de la serpiente.
            queue<path> BFS;
            char screen[WIDTH][HEIGHT];
            int next_move[WIDTH][HEIGHT];

            int dx[] = {-1, 0, 1, 0};
            int dy[] = {0, -1, 0, 1};
            int direction[] = {KEY_LEFT, KEY_UP, KEY_RIGHT, KEY_DOWN};

            BFS.push(path(food.x, food.y));
            getMatrixFromScreen(screen, snake, food);
            screen[snake.head->x][snake.head->y] = ' ';
            memset(next_move, 0, sizeof(next_move));

            while (!BFS.empty()) {
                path current = BFS.front();
                BFS.pop();

                // Se encontró un camino válido.
                if (current.x == snake.head->x && current.y == snake.head->y) {
                    break;
                }

                // Intenta avanzar hacia las demás direcciones. Marcamos las
                // posiciones que vamos visitando.
                for (int i = 0; i < 4; ++i) {
                    path next(current.x - dx[i], current.y - dy[i]);
                    if (
                        MIN_X <= next.x && next.x <= MAX_X &&
                        MIN_Y <= next.y && next.y <= MAX_Y &&
                        screen[next.x][next.y] == ' '
                    ) {
                        screen[next.x][next.y] = 'V';
                        next_move[next.x][next.y] = direction[i];
                        BFS.push(next);
                    }
                }
            }

            return next_move[snake.head->x][snake.head->y];
        }

        // Demostración. La serpiente se moverá de manera autónoma siguiendo
        // la ruta más corta hacia la comida.
        static int demonstration() {
            load_screen("screen/demonstration.bin");

            unsigned int score = 0;

            Snake snake(WIDTH/2, HEIGHT/2, KEY_RIGHT);
            Food food(snake, time(0));

            while (get_key_pressed() != KEY_ESC) {
                int key_pressed = getShortestPathToFood(snake, food);
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
                    Sleep(90);
                }
                else {
                    break;
                }
            }

            return score;
        }
};

#endif // AI_H_INCLUDED
