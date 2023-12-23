#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <memory>

#include "TileType.h"
#include "Player.h"

class Tile {
    protected:
        TileType type;
        int position;
        Tile(void) {};
        Tile(TileType t, int p) : type(t), position(p) {};
        Tile(Tile& t) : type(t.type), position(t.position) {};

    public:
        TileType getType(void) const { return this->type; };
        virtual std::string toString(const std::vector<std::shared_ptr<Player>>& players) const = 0;
        std::string toCoordinates(void) const;
        friend class Board;

        static constexpr int ECONOMY_COUNT = 8;
        static constexpr int STANDARD_COUNT = 10;
        static constexpr int LUXURY_COUNT = 6;
};

#endif