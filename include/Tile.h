#ifndef TILE_H
#define TILE_H

#include "TileType.h"

class Tile {
    protected:
        TileType type;
        int position;

    public:
        Tile(void) {};
        virtual ~Tile() = 0;
        Tile(const Tile&) = delete;
        Tile& operator=(const Tile&) = delete;

        Tile(TileType t, int p) : type(t), position(p) {};
        TileType getType(void) const { return this->type; };
};

#endif