#include "Board.h"
#include <iostream>

#include "CornerTile.h"
#include "TileTerrain.h"

char nthLetter(int idx)
{
    if (idx < 0 || idx > 20) return ' ';
    return "ABCDEFGHILMNOPQRSTUVZ"[idx];
}

Board::Board(void) {
    for (int i = 0; i < Board::PLAYERS_COUNT; i++) this->players.push_back(std::make_shared<Player>());

    int economyCounter = 0, standardCounter = 0, luxuryCounter = 0;
    for (int i = 0; i < 28; i++) {
        if (i % 7 == 0) this->tiles.push_back(std::make_shared<CornerTile>(i));
        else {
            TileType tileType;
            switch (rand() % 3) {
                case 1:
                    if (luxuryCounter < Tile::LUXURY_COUNT) {
                        luxuryCounter++;
                        tileType = TileType::LUXURY;
                        break;
                    }
                case 2:
                    if (economyCounter < Tile::ECONOMY_COUNT) {
                        economyCounter++;
                        tileType = TileType::ECONOMY;
                        break;
                    }
                default:
                    standardCounter++;
                    tileType = TileType::STANDARD;
                    break;
            }

            this->tiles.push_back(std::make_shared<TileTerrain>(tileType, i));
        }
    }
    
    int startPosition = (rand() % 4) * 7; // 0, 7, 14 or 21
    this->tiles[startPosition] = std::make_shared<CornerTile>(TileType::START, startPosition);
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
    std::cout << "    ";
    for (int i = 0; i < Board::SIDE_LENGTH; i++)
        std::cout << "   " << i;

    std::cout << "\n";

    for (int row = 0; row < Board::SIDE_LENGTH; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            if (col == 0) std::cout << " " << nthLetter(row) << "    ";
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1) {
                int idx = (row + col >= 2 * row) ? row + col : (Board::SIDE_LENGTH * 4 - 4) - (row + col);
                std::cout << "|" << (char) this->tiles[idx]->type << "| ";
            } else
                std::cout << "    ";
        }
        std::cout << "\n";
    }
}

bool Board::buyTerrain(int position, std::shared_ptr<Player> player) {
    if (this->tiles[position].get()->getType() == TileType::CORNER || this->tiles[position].get()->getType() == TileType::START) return false;
    SideTile* tile = (SideTile*) this->tiles[position].get();
    
    if (player->getBalance() < tile->getPrice()) return false;
    player->withdraw(tile->getPrice());
    tile->owner = player;
    
    return true;
}