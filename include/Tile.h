// Author: Federico Zardo

#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <memory>

#include "TileType.h"
#include "Player.h"

/*
    Tile class which represents a tile of the board.
    It's an abstract class which is inherited by CornerTile and SideTile.
    It contains the type of the tile and its position on the board, and provides
    a function to convert the position to human-readable coordinates (row and column)
*/
class Tile {
    protected:
        TileType type;
        int position;
        Tile(void) {};
        Tile(TileType t, int p) : type(t), position(p) {};
        Tile(Tile& t) : type(t.type), position(t.position) {};

    public:
        virtual ~Tile() {};
        TileType getType(void) const { return this->type; };
        // Returns a representation of the tile following the format "type:building:current occupants"
        virtual std::string toString(const std::vector<std::shared_ptr<Player>>& players) const = 0;
        // Returns a human-readable coordinates (row and column) representation of the tile's position
        std::string toCoordinates(void) const;
        friend class Board;

        // Number of tiles of each type on the board
        static constexpr int ECONOMY_COUNT = 8;
        static constexpr int STANDARD_COUNT = 10;
        static constexpr int LUXURY_COUNT = 6;
};

#endif