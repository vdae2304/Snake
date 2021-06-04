#include "game/system.h"
#include "game/snake.h"
#include "game/food.h"
#include "game/scoreboard.h"
#include "game/game.h"
#include "game/ai.h"
int main() {
    set_window_size();
    while (true) {
        int option = Game::displayTitleScreen();
        unsigned int score;
        switch (option) {
            case 0:
                score = Game::newGame();
                Game::displayGameOver(score);
                Scoreboard::displayScoreboard();
                break;
            case 1:
                AI::demonstration();
                break;
            case 2:
                Scoreboard::displayScoreboard();
                break;
        }
    }
    return 0;
}
