#include "game/system.h"
#include "game/snake.h"
#include "game/food.h"
#include "game/scoreboard.h"
#include "game/game.h"
int main() {
    set_window_size();
    while (true) {
        Game::displayTitleScreen();
        unsigned int score = Game::newGame();
        Game::displayGameOver(score);
        Scoreboard::displayScoreboard();
    }
    return 0;
}
