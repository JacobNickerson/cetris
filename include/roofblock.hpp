#ifndef ROOFBLOCK_HPP
#define ROOFBLOCK_HPP

#include "block.hpp"

class RoofBlock : public Block {
    private:
        const int colu;
        const int row;
        std::optional<Color> colo;

    public:
        void activate(Color _);

};

#endif