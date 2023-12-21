#ifndef TILE_TERRAIN_H
#define TILE_TERRAIN_H

#include "SideTile.h"

class TileTerrain : public SideTile {
    public:
        TileTerrain(void) {};
        TileTerrain(TileType t, int p) : SideTile(t, p) {};
        int getPrice(void) override;
        int getRent(void) override { return 0; };
};

#endif