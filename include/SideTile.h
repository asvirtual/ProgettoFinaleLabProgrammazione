#ifndef SIDE_TILE_H
#define SIDE_TILE_H

#include <memory>

#include "Tile.h"
#include "Player.h"
#include "TileBuilding.h"

class Player;

class SideTile : public Tile {
    private:
        std::shared_ptr<Player> owner;
        TileBuilding building;

    public:
        SideTile(void) {};
        SideTile(TileType t, int p) : Tile(t, p), building(TileBuilding::NONE) {};
        ~SideTile() {};
        int getHousePrice(void);
        int getHotelPrice(void);
        int getTerrainPrice(void);
        int getRent(void);
        friend class Board;
};

#endif