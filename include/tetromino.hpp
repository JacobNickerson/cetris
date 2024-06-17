#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>
#include <utility>

#include "block.hpp"
#include "board.hpp"

// Tetromino Rotation
// enum class rotation { I, O, T, J, L, S, Z, };

class Tetromino {
    private:
        std::array<Block*, 4> blocks;
        Block* pivot;
        int rotation; // this is kinda scuffed, perhaps that enum thing would be better
        // TType type;
        Color colo;


    public:
        // Initialization of a tetromino.
        Tetromino(Block* piv, Color colo) : pivot(piv), rotation(0), colo(colo) {
            expandPivot();
        };

        // Input a pointer pointing to the spawn point of the pivot point, Tetromino constructed from this, returns
        // false if constructing Tetromino results in a collision
        bool spawnTetromino(Block* piv, Board& board);

        // Returns the type of the tetromino.
        // TType getType();

        // Attempts to rotate the tetromino 90 degrees to the right.
        // Returns true if success, false if not.
        bool rotateRight();

        // Attempts to rotate the tetromino 90 degrees to the left.
        // Returns true if success, false if not.
        bool rotateLeft();

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
        virtual void expandPivot();
        virtual void expandPivot(int& new_rotation, std::array<Block*, 4>& new_blocks);


};

#endif
