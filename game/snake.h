#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

class AI;
class Food;

class Snake {
    protected:
        struct node {
            int x, y;
            node *next;

            node(int x, int y) {
                this->x = x;
                this->y = y;
                this->next = nullptr;
            }
        };

        node *head, *tail;
        int direction, length;

        friend class AI;
        friend class Food;

    public:
        // Inicializa la serpiente.
        Snake(int start_x, int start_y, int initial_direction) {
            this->head = new node(start_x, start_y);
            this->tail = this->head;
            this->direction = initial_direction;
            this->length = 1;
            print_at_position(start_x, start_y, '#', false);
        }

        // Destruye la serpiente.
        ~Snake() {
            node *it = this->tail;
            while (it != nullptr) {
                node *it_copy = it;
                it = it->next;
                delete it_copy;
            }
        }

        // Desplaza la cabeza de la serpiente.
        void push_head(int x, int y) {
            this->head->next = new node(x, y);
            this->head = this->head->next;
            this->length++;
            print_at_position(x, y, '#', false);
        }

        // Desplaza la cola de la serpiente.
        void pop_tail() {
            node *old_tail = this->tail;
            this->tail = this->tail->next;
            this->length--;
            print_at_position(old_tail->x, old_tail->y, ' ', false);
            delete old_tail;
        }

        // Devuelve true si la posición pasada como argumento está ocupada por
        // la serpiente.
        bool is_occupied(int x, int y) const {
            for (node *it = this->tail; it != nullptr; it = it->next) {
                if (it->x == x && it->y == y) {
                    return true;
                }
            }
            return false;
        }

        // Mueve la serpiente en la dirección indicada. Guarda la nueva posición
        // en new_x y new_y.
        // Devuelve true si fue un movimiento válido y false en caso contrario
        // (por ejemplo, la serpiente trató de comerse a sí misma o chocó contra
        // una pared).
        bool move(int key_pressed, int &new_x, int &new_y) {
            // Verifica que el nuevo movimiento no sea un giro de 180°.
            if (
                (key_pressed == KEY_LEFT && this->direction != KEY_RIGHT) ||
                (key_pressed == KEY_RIGHT && this->direction != KEY_LEFT) ||
                (key_pressed == KEY_UP && this->direction != KEY_DOWN) ||
                (key_pressed == KEY_DOWN && this->direction != KEY_UP)
            ) {
                this->direction = key_pressed;
            }

            // Avanza en la dirección indicada.
            new_x = this->head->x;
            new_y = this->head->y;
            switch (this->direction) {
                case KEY_LEFT:
                    new_x--;
                    break;
                case KEY_RIGHT:
                    new_x++;
                    break;
                case KEY_UP:
                    new_y--;
                    break;
                case KEY_DOWN:
                    new_y++;
                    break;
            }

            // ¡La serpiente trató de comerse a sí misma!
            if (this->is_occupied(new_x, new_y)) {
                return false;
            }
            // ¡La serpiente se salió de la pantalla!
            if (
                new_x < MIN_X || new_x > MAX_X || new_y < MIN_Y || new_y > MAX_Y
            ) {
                return false;
            }
            // ¡La serpiente ya no puede crecer más!
            if (this->length + 1 == (MAX_X - MIN_X + 1)*(MAX_Y - MIN_Y + 1)) {
                return false;
            }
            return true;
        }
};

#endif // SNAKE_H_INCLUDED
