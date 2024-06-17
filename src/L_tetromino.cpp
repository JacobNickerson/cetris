#include "L_tetromino.hpp"
#include "tetromino.hpp"

const std::array<std::array<std::pair<int, int>, 4>, 4> rotation_positions = {{
        { {{0,-1}, {0,0}, {0, 1}, {-1,1}} },
        { {{-1,0}, {0,0}, {1,0}, {1,1}} },
        { {{1,-1}, {0,-1}, {0,0}, {0,1}} },
        { {{-1,-1}, {-1,0}, {0,0}, {1,0}} },
}};

