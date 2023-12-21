#ifndef CORNER_TILE_H
#define CORNER_TILE_H

#include "Tile.h"

class CornerTile : public Tile {
    public:
        CornerTile(void) {};
        CornerTile(int p) : Tile(TileType::CORNER, p) {};
        CornerTile(TileType t, int p) : Tile(t, p) {};
        bool isStart(void) const { return this->type == TileType::START; };
};

#endif