#ifndef SIDE_TILE_H
#define SIDE_TILE_H

#include "Tile.h"

class SideTile : public Tile {
    public:
        SideTile(void) {};
        SideTile(TileType t, int p) : Tile(t, p) {};
        virtual int getPrice(void) = 0;
        virtual int getRent(void) = 0;
};

#endif