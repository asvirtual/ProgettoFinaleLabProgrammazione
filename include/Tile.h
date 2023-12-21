#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
    protected:
        TileType type;
        int position;
        Tile(void) {};

    public:
        Tile(TileType t, int p) : type(t), position(p) {};
        TileType getType(void) const { return this->type; };
        friend class Board;
};

#endif