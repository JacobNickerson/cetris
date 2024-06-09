#ifndef COLOR_HPP
#define COLOR_HPP

struct Color {
    unsigned short r;
    unsigned short g;
    unsigned short b;

    Color(short r, short g, short b) : r(r), g(g), b(b) {};
};

#endif
