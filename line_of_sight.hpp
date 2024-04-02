#ifndef SB_LOS_HPP
#define SB_LOS_HPP

#include <stdint.h>
#include <vector>

// Spencer Banasik - 3/30/2024
// This algorithm aims to, given a 2d array with sight blockers, caluclate the line of sight
// from any given position. Right now the main file just outputs the calculated array.
// Big TODOS:
// - Convert our 2D vectors into 1D vectors 

// TODO: If we really wanted to optimize our performance, we could return a 1d array,
// and I may consider doing this in the future. As a proof of concept, this is fine.
namespace SB_LOS {

// Given a set of terrain where 1 is blocked and 0 is free,
// return an array of sight where ' ' is free, 'X' is obstructed, and 'W' is the wall causing the obstruction.
std::vector<std::vector<char>> line_of_sight(const std::vector<std::vector<char>>& terrain, int x, int y);
};
#endif