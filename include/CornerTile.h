#ifndef CORNER_TILE_H
#define CORNER_TILE_H

#include "Tile.h"

class CornerTile : public Tile {
    public:
        CornerTile(void) {};
        ~CornerTile() {};
        CornerTile(int p) : Tile(TileType::CORNER, p) {};
        CornerTile(const CornerTile& t) : Tile(t.type, t.position) {};
        CornerTile& operator=(const CornerTile& t) { return *this; };
        bool isStart(void) const { return this->type == TileType::START; };
};

#endif