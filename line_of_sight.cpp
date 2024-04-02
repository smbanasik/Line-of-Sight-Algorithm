#include "line_of_sight.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "line_algorithm.hpp"

// TODO: it may be useful to make some utility that handles the creation of things like this,
// and add them to a personal library
// Also, doesn't actually create a square. It can make rectangles. Bad name.
std::vector<std::vector<char>> create_square(int size_x, int size_y) {
    std::vector<std::vector<char>> square;

    for (int i = 0; i < size_x; i++)
        square.push_back(std::vector<char>(size_y, 'X'));

    return square;
}

void make_los(const std::vector<std::vector<char>>& terrain,
    std::vector<std::vector<char>>& los, const std::vector<SB_LINE::Coordinate>& line) {
    char tile_data = 0;
    bool blocked = false;

    for (int j = 0; j < line.size(); j++) {

        int line_x = line[j].x, line_y = line[j].y;

        tile_data = terrain[line_y][line_x];

        if (tile_data == 1) {
            blocked = true;
            los[line_y][line_x] = 'W';
        }

        if (blocked == true)
            break;
        else
            los[line_y][line_x] = ' ';

    }
}

std::vector<std::vector<char>> SB_LOS::line_of_sight(const std::vector<std::vector<char>>& terrain, int x, int y) {

    std::vector<std::vector<char>> los = create_square(terrain.size(), terrain[0].size());

    // TODO: This only makes sense if we have a contiguous array and the data in the array is large enough to impact cache hits
    // The most optimal way to do this would be like so:
    // Let H be values we explore when handling the top and bottom (horizontal traversal)
    // and V be values we explore when handling the sides (vertical traversal)
    // HHHHHHH
    // H00000V
    // V00000V
    // V00000V
    // V00000H
    // HHHHHHH
    // Additionally, when handling the sides, we can horizontally traverse like so:
    // H000001
    // 1000002
    // 2000003
    // 300000H

    for (int z = 0; z < 2; z++) {
        int row = z * (terrain.size() - 1);
        for (int i = 0; i < terrain[row].size(); i++) {

            std::vector<SB_LINE::Coordinate> line = SB_LINE::draw_line32b(x, i, y, row);
            make_los(terrain, los, line);
        }
    }

    for (int z = 0; z < 2; z++) {
        int column = z * (terrain[0].size() - 1);
        for (int i = 0; i < terrain.size(); i++) {

            std::vector<SB_LINE::Coordinate> line = SB_LINE::draw_line32b(x, column, y, i);
            make_los(terrain, los, line);
        }
    }


    return los;
}

#define SB_LOS_TESTING
#ifdef SB_LOS_TESTING

void initialize_terrain(std::vector<std::vector<char>>& terrain, std::string input) {

    std::ifstream in_file;

    in_file.open(input);
    if (!in_file.is_open())
        throw;

    std::string buffer;
    while (std::getline(in_file, buffer)) {

        std::vector<char> temp;

        for (int i = 0; i < buffer.size(); i++) {
            if (buffer[i] == '0')
                temp.push_back(0);
            else
                temp.push_back(1);
        }

        terrain.push_back(temp);

    }
    in_file.close();
}

void print_terrain(const std::vector<std::vector<char>>& terrain) {

    for (int i = 0; i < terrain.size(); i++) {
        for (int j = 0; j < terrain[i].size(); j++) {
            std::cout << (short)terrain[i][j];
        }
        std::cout << "\n";
    }

}
void print_los(const std::vector<std::vector<char>>& terrain) {

    for (int i = 0; i < terrain.size(); i++) {
        for (int j = 0; j < terrain[i].size(); j++) {
            std::cout << terrain[i][j];
        }
        std::cout << "\n";
    }

}

void print_vector(const std::vector<SB_LINE::Coordinate>& vals) {

    std::cout << "(x, y) ";
    for (int i = 0; i < vals.size(); i++) {
        std::cout << "(" << vals[i].x << ", " << vals[i].y << ") ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<std::vector<char>> terrain;

    initialize_terrain(terrain, "infile.txt");

    print_terrain(terrain);
    
    std::cout << "\n";

    std::vector<std::vector<char>> los = SB_LOS::line_of_sight(terrain, 20, 10);

    print_los(los);

}
#endif