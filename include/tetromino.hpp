#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <utility>
#include <iostream>

#include "block.hpp"
#include "board.hpp"


class Tetromino {
    public:
        Tetromino() : rotation(0), colo(sf::Color(255,0,0)) {
            for (size_t i = 0; i < blocks.size(); i++) {
                blocks[i] = nullptr;
            }
        };

        Tetromino(sf::Color colo) : rotation(0), colo(colo) {
            for (size_t i = 0; i < blocks.size(); i++) {
                blocks[i] = nullptr;
            }
        };

        // Initialization of a tetromino.
        Tetromino(Block* piv, sf::Color colo) : pivot(piv), rotation(0), colo(colo) {
            for (size_t i = 0; i < blocks.size(); i++) {
                blocks[i] = piv;
            }
        };

        // Deletion of a tetromino
        ~Tetromino() {
            for (size_t i = 0; i < blocks.size(); i++) {
                delete blocks[i];
                blocks[i] = nullptr;
            }
            delete pivot;
            pivot = nullptr;
        }

        // Tetromino constructed from pivot point returns
        // false if constructing Tetromino results in a collision
        virtual bool constructTetromino(Board& board);

        // Attempts to rotate the tetromino 90 degrees to the right.
        // Returns true if success, false if not.
        virtual bool rotateRight(Board& board);

        // Attempts to rotate the tetromino 90 degrees to the left.
        // Returns true if success, false if not.
        virtual bool rotateLeft(Board& board);

        // Moves the tetromino up.  (Would this really get used?)
        // Returns true if success, false if not.
        bool up(Board& board);

        // Moves the tetromino down.
        // Returns true if success, false if not.
        bool down(Board& board);

        // Moves the tetromino left.
        // Returns true if success, false if not.
        bool left(Board& board);

        // Moves the tetromino right. 
        // Returns true if success, false if not.
        bool right(Board& board);

        // Shoves the tetromino to the ghost position.
        // Returns true if success, false if not.
        bool hardDrop(Board& Board);

        // Calculates how far down the ghost position is.
        int ghostPosition(Board& board);

        // Moves the pivot point to point i,j
        void movePivot(int colu, int row, Board& board);

        // Generates the tetrominos current orientation on the board according to its
        // orientation and pivot point location
        virtual void expandPivot(Board& board);
        virtual void expandPivot(int new_rotation, std::array<Block*, 4>& new_blocks, Board& board);

        // Activates all the blocks in a tetromino
        void activate();

        // Deactivates all the blocks in a tetromino
        void deactivate();

        // returns the array of blocks in a tetromino
        std::array<Block*, 4> getBlocks();
        
        // return the color of the tetromino
        sf::Color getColor();

        // sets a tetromino to default rotation, no pivot point, and no color
        void reset();

        // sets a tetromino to have a specified rotation, a specified pivot point
        void set(int rot, Block* pivot);

        // returns offsets from rotated_positions for position rotation = 0
        virtual std::array<std::pair<int, int>, 4> getRotationPositions();

    protected:
        std::array<Block*, 4> blocks;
        Block* pivot;
        int rotation; // this is kinda scuffed, perhaps that enum thing would be better
        std::array<std::array<std::pair<int, int>, 4>, 4> rotation_positions; 
        sf::Color colo;
};

#endif
