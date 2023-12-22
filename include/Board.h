#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <random>

#include "Tile.h"
#include "CornerTile.h"
#include "TileTerrain.h"
#include "TileHouse.h"
#include "Player.h"
#include "BotPlayer.h"

class Board {
    private:
        static constexpr int SIDE_LENGTH = 8;
        static constexpr int PLAYERS_COUNT = 4;

        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Player>> players;

    public:
        Board(void);
        void print(void);
        void buyTerrain(SideTile* tile, std::shared_ptr<Player> player);
        void payRent(SideTile* tile, std::shared_ptr<Player> player);
        void buildHouse(TileTerrain* tile); // TODO
        void buildHotel(TileHouse* tile); // TODO
        void move(std::shared_ptr<Player> player);
};

#endif