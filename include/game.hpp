#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "board.hpp"

class Game {
    private:
        Board board;
        bool game_over;

    public:
        Game() {
            Board board;
            game_over = false;
        }

        void start();

};

#endif