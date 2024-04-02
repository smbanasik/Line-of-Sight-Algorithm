// Spencer Banasik - 4/02/2024
// This algorithm provides an implementation of Bresenham's line algorithm,
// and covers all cases. It assumes all work with numbers will be positive,
// since all that this will be used for right now involves indices.

#ifndef SB_LINE_ALGORITHM_HPP
#define SB_LINE_ALGORITHM_HPP

#include <stdint.h>
#include <vector>

namespace SB_LINE {

struct Coordinate {
    uint32_t x, y;

    Coordinate(uint32_t x, uint32_t y) : x(x), y(y) {
    };
};

// Given two points, draw a line from point 0 to point 1 and return a vector of XY coordinates.
std::vector<Coordinate> draw_line32b(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1);

}
#endif