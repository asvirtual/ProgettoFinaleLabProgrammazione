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


    // std::cout << this->tiles.size() << "\n";
    // for (int i = 0; i < this->tiles.size(); i++) {
        
    //     std::cout << (char) this->tiles[i]->getType() << ", " << this->tiles[i]->position << "\n";
    // }

    // std::cout << "end\n";

    for (int row = 0; row < Board::SIDE_LENGT; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            int idx = row + col > 2 * row ? row + col : (Board::SIDE_LENGTH * 2 - 4 - 1) - (row + col);
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1)
                std::cout << (char) this->tiles[row]->type << "\n";
        }
    }


    // for (int i = 0; i < Board::SIDE_LENGTH; i++) {
    //     for (int j = 0; j < Board::SIDE_LENGTH; j++) {
    //         if (j == 0 || j == Board::SIDE_LENGTH - 1 || i == 0 || i == Board::SIDE_LENGTH - 1) {
    //             int idx = i + (j - 7) % 7;
    //             std::cout << "|" << (char) (this->tiles[idx]->getType()) << "| ";
    //         } else {
    //             std::cout << "    ";
    //         }
    //     }
    //     std::cout << "\n";
    // }
}