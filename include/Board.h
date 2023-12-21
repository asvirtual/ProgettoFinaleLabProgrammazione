#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "Tile.h"
#include "Player.h"

class Board {
    private:
        static constexpr int SIDE_LENGTH = 8;
        std::vector<std::unique_ptr<Tile>> tiles;
        std::vector<std::unique_ptr<Player>> players;

    public:
        Board(void);
        // Board(std::vector<std::unique_ptr<Tile>> t, std::vector<std::unique_ptr<Player>> p) : tiles(t), players(p) {};
        void print(void);
};

#endif