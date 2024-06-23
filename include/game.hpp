#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "sprite_board.hpp"
#include <vector>

enum class GameState {
    Title,
    GameRunning,
    GameOver
};

class Game {
    private:
        Board game_board;
        SpriteBoard game_sprite_board;
        GameState game_state;
        int score;

    public:
        Game() {
            game_state = GameState::Title;
            score = 0;
        }

        void run();

        // places the tetromino in the current position and spawns a new one at ()
        bool spawnTetromino(Tetromino& tetromino);

        // places the tetromino in the current position and spawns one at a given coordinate
        bool spawnTetromino(Tetromino& tetromino, int row, int col);

        void titleScreen(sf::RenderWindow& window);
        
        void playGame(sf::RenderWindow& window);

        bool initializeSprites();

        void reset();
};

#endif