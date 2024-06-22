#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include <vector>

enum class GameState {
    Title,
    GameRunning,
    GameOver
};

class Game {
    private:
        Board game_board;
        GameState game_state;
        bool live_block;

    public:
        Game() {
            game_state = GameState::GameRunning;
            live_block = false;
        }

        void run();

        void playGame();

};

#endif