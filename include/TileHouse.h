#ifndef TILE_HOUSE_H
#define TILE_HOUSE_H

#include "TileTerrain.h"

class TileHouse : public TileTerrain {
    public:
        TileHouse(void) {};
        TileHouse(TileType t, int p) : TileTerrain(t, p) {};
        int getPrice(void) override;
        int getRent(void) override;
};

#endif