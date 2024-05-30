# Line-of-Sight-Algorithm
A proof of concept implementation for a line of sight algorithm. Given a two dimensional tileset of walls and open space, and a position, the algorithm will calculate
what may be seen from that position. Since this serves as a starting point, inputs and outputs should be changed to suit the users needs. I made use of Bresenham's line algorithm
to calculate the line between the start point and the end of the tileset. I opted to use this algorithm since its operations are less intensive to calculate.

This is a fairly naive approach, and the inputs and outputs should be flattened to ensure contiguous memory. Ideally, finding a method to separate 
the calculations and element access from the memory would be ideal, since then a vertical line wouldn't traverse an array vertically (which is not good for caches!).

## Adding to a project

To add to a project, add the two header files to the director where your headers are, and add the source file to the directory where your source files are.

## Usage

### File Descriptions

`line_algorithm`, the `.cpp` and `.hpp` files, contain the implementation of Bresenham's algorithm.
`line_of_sight` contains the implementation of the actual line of sight algorithm.

### Usage

To use the algorithm, `#include` the `line_of_sight.hpp` file and call the `line_of_sight` function.
It takes a 2d array of 1's and 0's, where 0 is open space and 1 is a wall. Additionally, it takes an X and Y coordinate, which is used to define the 
start point for drawing the lines. This is the point of reference for the algorithm.

## How to Contribute

If you have some improvement to make, make a pull request. Try to keep the format similar to what has been written.
