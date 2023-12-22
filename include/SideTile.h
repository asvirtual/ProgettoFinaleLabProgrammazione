#ifndef SIDE_TILE_H
#define SIDE_TILE_H

#include <memory>

#include "Tile.h"
#include "Player.h"

class SideTile : public Tile {
    private:
        std::shared_ptr<Player> owner;
        int housePrice;
        int hotelPrice;

    public:
        SideTile(void) {};
        virtual ~SideTile() {};
        SideTile(TileType t, int p);
        int getHousePrice(void) const { return this->housePrice; };
        int getHotelPrice(void) const { return this->hotelPrice; };
        virtual int getPrice(void) = 0;
        virtual int getRent(void) = 0;
        friend class Board;
};

#endif