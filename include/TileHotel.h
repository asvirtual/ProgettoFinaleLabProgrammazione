#ifndef TILE_HOTEL_H
#define TILE_HOTEL_H

#include "SideTile.h"

class TileHotel : public SideTile {
    public:
        TileHotel(void) {};
        ~TileHotel() {};
        TileHotel(TileType t, int p) : SideTile(t, p) {};
        int getPrice(void) override;
        int getRent(void) override;
};

#endif