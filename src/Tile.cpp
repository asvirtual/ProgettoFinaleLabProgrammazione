// Author: Federico Zardo

#include <string>

#include "Tile.h"
#include "Board.h"
#include "monopoly.h"

std::string Tile::toCoordinates(void) const {
    /* Vector's indexes for every tile on the board

        0  1  2  3  4  5  6  7
        27                   8
        26                   9
        25                   10
        24                   11
        23                   12
        22                   13
        21 20 19 18 17 16 15 14
    */

    /* Tiles' vector index (0..27) matched to their human-readable coordinates (A1..H8)

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

    /*
        Performs different calculations based on the row/column of the tile on the board
    */

    std::string coords;

    // Upper row, row is "A", column is array's index + 1 ([0-7] -> [1-8])
    if (this->position <= Board::TILES_COUNT / 4) 
        coords = monopUtil::nthLetter(0) + std::to_string(this->position + 1);

    // Right column, row is array's index + 1 corresponding letter ([8-14] -> [1-7] -> [B-H]), column is 8
    else if (this->position <= Board::TILES_COUNT / 2) 
        coords = monopUtil::nthLetter(this->position - 7) + std::to_string(8);

    // Lower row, row is "H", column is | array's index - (3/4 * tiles count + 1) | ([21-14] -> [1-8])
    else if (this->position <= 3 * Board::TILES_COUNT / 4) 
        coords = monopUtil::nthLetter(7) + std::to_string(abs(this->position - (3 * Board::TILES_COUNT / 4 + 1)));

    // Left column, row is | array's index - tiles count | corresponding letter ([27-22] -> [2-7] -> [B-G]), column is 1
    else 
        coords = monopUtil::nthLetter(abs(this->position - Board::TILES_COUNT)) + std::to_string(1);

    return coords;
}