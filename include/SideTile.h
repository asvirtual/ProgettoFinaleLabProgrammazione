// Author: Andrea Boscarin

#ifndef SIDE_TILE_H
#define SIDE_TILE_H

#include <string>
#include <memory>

#include "Tile.h"
#include "Player.h"
#include "TileBuilding.h"

class Player; // Forward declaration

/*
    SideTile class which represents a side tile of the board.
    It adds to the parent class Tile some methods to handle the tile's building and owner.
*/
class SideTile : public Tile {
    private:
        std::shared_ptr<Player> owner;
        TileBuilding building;

    public:
        static constexpr int TILES_TYPES_COUNT = 3;

        // The constuctors call the parent constructor to handle inherited fields, and initialize the SideTile's fields
        SideTile(void) : Tile() {};
        SideTile(SideTile& t) : Tile(t), owner(t.owner), building(t.building) {}; // Copy constructor
        // Creates a SideTile knowing its type and position, with no building
        SideTile(TileType t, int p) : Tile(t, p), building(TileBuilding::NONE) { if (t == TileType::CORNER || t == TileType::START) throw std::invalid_argument("Invalid tile type"); };
        ~SideTile() {};
        int getHousePrice(void); // Returns the price of a house on the tile, based on its type
        int getHotelPrice(void); // Returns the price of a hotel on the tile, based on its type
        int getTerrainPrice(void); // Returns the price of the tile, based on its type
        int getRent(void); // Returns the rent of the tile, based on its type and building
        std::string toString(const std::vector<std::shared_ptr<Player>>& players) const;
        friend class Board;
};

#endif