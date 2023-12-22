#ifndef TILE_HOUSE_H
#define TILE_HOUSE_H

#include "SideTile.h"

class TileHouse : public SideTile {
    public:
        TileHouse(void) {};
        ~TileHouse() {};
        TileHouse(TileType t, int p) : SideTile(t, p) {};
        int getPrice(void) override;
        int getRent(void) override;
};

#endif