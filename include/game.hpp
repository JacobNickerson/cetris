#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "board.hpp"

enum class GameState {
    Title,
    GameRunning,
    GameOver
};

class Game {
    private:
        Board board;
        GameState game_state;

    public:
        Game() {
            game_state = GameState::Title;
        }

        void run();

        void playGame();

};

#endif