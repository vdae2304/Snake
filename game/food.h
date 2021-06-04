#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

class AI;

class Food {
    protected:
        int x, y;
        default_random_engine generator;

        friend class AI;

    public:
        // Inicializa la comida.
        Food(const Snake &snake, int seed) {
            this->generator.seed(seed);
            this->gen_new_food(snake);
        }

        // Verifica si la serpiente acaba de comer la comida.
        bool ate_food(const Snake &snake) const {
            return (this->x == snake.head->x && this->y == snake.head->y);
        }

        // Genera una nueva posición para la comida.
        void gen_new_food(const Snake &snake) {
            uniform_int_distribution<int> random_x(MIN_X, MAX_X);
            uniform_int_distribution<int> random_y(MIN_Y, MAX_Y);

            do {
                this->x = random_x(generator);
                this->y = random_y(generator);
            }
            while (snake.is_occupied(this->x, this->y));

            print_at_position(this->x, this->y, 'O', false);
        }
};

#endif // FOOD_H_INCLUDED
