#include "Board.h"
#include <iostream>

#include "CornerTile.h"
#include "TileTerrain.h"

Board::Board(void) {
    for (int i = 0; i < 28; i++) {
        if (i % 7 == 0) this->tiles.push_back(std::unique_ptr<Tile>(new CornerTile(i)));
        else this->tiles.push_back(std::unique_ptr<Tile>(new TileTerrain(TileType::ECONOMY, i)));
    }
}

void Board::print(void) {
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

    for (int row = 0; row < Board::SIDE_LENGTH; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            int idx = (row + col >= 2 * row) ? row + col : (Board::SIDE_LENGTH * 4 - 4) - (row + col);
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1) 
                std::cout << "|" << (char) this->tiles[idx]->type << "| ";
            else 
                std::cout << "    ";
        }
        std::cout << "\n";
    }

}