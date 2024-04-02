#include "line_algorithm.hpp"

#include <stdint.h>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<SB_LINE::Coordinate> bresenham_shallow_32(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1) {
    std::vector<SB_LINE::Coordinate> values;

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t yi = 1;

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    int32_t D = (dy << 1) - dx;
    uint32_t y = y0;

    for (uint32_t i = x0; i <= x1; i++) {
        values.push_back(SB_LINE::Coordinate{ i, y });

        if (D > 0) {
            y = y + yi;
            D = D + ((dy - dx) << 1);
        }
        else {
            D = D + (dy << 1);
        }
    }

    return values;
}

std::vector<SB_LINE::Coordinate> bresenham_steep_32(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1) {
    std::vector<SB_LINE::Coordinate> values;

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;
    int32_t xi = 1;

    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    int32_t D = (dx << 1) - dy;
    uint32_t x = x0;

    for (uint32_t i = y0; i <= y1; i++) {
        values.push_back(SB_LINE::Coordinate{ x, i });

        if (D > 0) {
            x = x + xi;
            D = D + ((dx - dy) << 1);
        }
        else {
            D = D + (dx << 1);
        }
    }

    return values;
}

std::vector<SB_LINE::Coordinate> SB_LINE::draw_line32b(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1) {
    std::vector<SB_LINE::Coordinate> line;

    if (x0 - x1 != 0 && y0 - y1 != 0)
        goto diagonal;

    if (x0 - x1 == 0 && y0 - y1 == 0) {
        line.push_back(Coordinate{ x0, y0 });
        return line;
    }

    if (x0 - x1 == 0) {
        if (y0 > y1) {
            for (int i = 0; i <= y0 - y1; i++) {
                line.push_back(Coordinate{ x0, y0 - i });
            }
        }
        else {
            for (int i = 0; i <= y1 - y0; i++) {
                line.push_back(Coordinate{ x0, y0 + i });
            }
        }
    }
    else {
        if (x0 > x1) {
            for (int i = 0; i <= x0 - x1; i++) {
                line.push_back(Coordinate{ x0 - i, y0 });
            }
        }
        else {
            for (int i = 0; i <= x1 - x0; i++) {
                line.push_back(Coordinate{ x0 + i, y0 });
            }
        }
    }
    return line;

diagonal:
    if (std::abs(static_cast<int32_t>(y1 - y0)) < std::abs(static_cast<int32_t>(x1 - x0))) {
        if (x0 > x1) {
            line = bresenham_shallow_32(x1, x0, y1, y0);
            std::reverse(line.begin(), line.end());
        }
        else {
            line = bresenham_shallow_32(x0, x1, y0, y1);
        }
    }
    else {
        if (y0 > y1) {
            line = bresenham_steep_32(x1, x0, y1, y0);
            std::reverse(line.begin(), line.end());
        }
        else {
            line = bresenham_steep_32(x0, x1, y0, y1);
        }
    }

    return line;
}