#ifndef SIDE_TILE_H
#define SIDE_TILE_H

#include <string>
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
        static constexpr int TILES_TYPES_COUNT = 3;

        SideTile(void) {};
        SideTile(SideTile& t) : Tile(t), owner(t.owner), building(t.building) {};
        SideTile(TileType t, int p) : Tile(t, p), building(TileBuilding::NONE) {};
        ~SideTile() {};
        int getHousePrice(void);
        int getHotelPrice(void);
        int getTerrainPrice(void);
        int getRent(void);
        std::string toString(const std::vector<std::shared_ptr<Player>>& players) const;
        friend class Board;
};

#endif