#ifndef CORNER_TILE_H
#define CORNER_TILE_H

#include <string>

#include "Player.h"
#include "Tile.h"

class CornerTile : public Tile {
    public:
        CornerTile(void) {};
        CornerTile(int p) : Tile(TileType::CORNER, p) {};
        CornerTile(TileType t, int p) : Tile(t, p) {};
        bool isStart(void) const { return this->type == TileType::START; };
        std::string toString(const std::vector<std::shared_ptr<Player>>& players) const;
};

#endif