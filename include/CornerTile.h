#ifndef CORNER_TILE_H
#define CORNER_TILE_H

#include <string>

#include "Player.h"
#include "Tile.h"

/*
    CornerTile class which represents a corner tile of the board.
    It adds to the parent class Tile a method to check if the tile is the start tile.
*/
class CornerTile : public Tile {
    public:
        CornerTile(void) : Tile() {};
        CornerTile(int p) : Tile(TileType::CORNER, p) {};
        CornerTile(TileType t, int p) : Tile(t, p) { if (t != TileType::CORNER && t != TileType::START) throw std::invalid_argument("Invalid tile type"); };
        bool isStart(void) const { return this->type == TileType::START; };
        std::string toString(const std::vector<std::shared_ptr<Player>>& players) const;
};

#endif