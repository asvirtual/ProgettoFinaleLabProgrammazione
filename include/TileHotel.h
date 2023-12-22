#ifndef TILE_HOTEL_H
#define TILE_HOTEL_H

#include "TileHouse.h"

class TileHotel : public TileHouse {
    public:
        TileHotel(void) {};
        TileHotel(TileType t, int p) : TileHouse(t, p) {};
        int getPrice(void) override;
        int getRent(void) override;
};

#endif