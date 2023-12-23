#include <string>

#include "Tile.h"
#include "Board.h"
#include "monopoly.h"

std::string Tile::toCoordinates(void) const {
    // 0 1 2 3 4 ... 27
    /*
        0  1  2  3  4  5  6  7
        27                   8
        26                   9
        25                   10
        24                   11
        23                   12
        22                   13
        21 20 19 18 17 16 15 14
    */
    /*
           1  2  3  4  5  6  7  8
        A  0  1  2  3  4  5  6  7  A
        B  27                   8  B
        C  26                   9  C
        D  25                   10 D
        E  24                   11 E
        F  23                   12 F  
        G  22                   13 G
        H  21 20 19 18 17 16 15 14 H
           1  2  3  4  5  6  7  8
    */

    std::string coords;

    if (this->position <= Board::TILES_COUNT / 4) coords = nthLetter(0) + std::to_string(this->position + 1);
    else if (this->position <= Board::TILES_COUNT / 2) coords = nthLetter(this->position - 7) + std::to_string(8);
    else if (this->position <= 3 * Board::TILES_COUNT / 4) coords = nthLetter(7) + std::to_string(abs(this->position - (Board::TILES_COUNT / 4 * 3 + 1)));
    else coords = nthLetter(abs(this->position - Board::TILES_COUNT)) + std::to_string(1);

    return coords;
}