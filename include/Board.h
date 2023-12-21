#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <random>

#include "Tile.h"
#include "Player.h"

class Board {
    private:
        static constexpr int SIDE_LENGTH = 8;
        static constexpr int PLAYERS_COUNT = 4;

        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Player>> players;

    public:
        Board(void);
        void print(void);
        bool buyTerrain(int position, std::shared_ptr<Player> player);
        void payRent(int position, std::shared_ptr<Player> player);
};

#endif