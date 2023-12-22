#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <random>
#include <string>

#include "Tile.h"
#include "CornerTile.h"
#include "SideTile.h"
#include "Player.h"
#include "BotPlayer.h"
#include "helperFunctions.h"

class Board {
    private:
        static constexpr int SIDE_LENGTH = 8;
        static constexpr int PLAYERS_COUNT = 4;
        static constexpr int MAX_TURNS = 100;

        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Player>> players;
        int turnsCounter;
        const char* commArg;

    public:
        Board(const char* arg);
        const std::vector<std::shared_ptr<Player>>& getPlayers(void) const { return this->players; };
        void print(void);
        void buyTerrain(SideTile* tile, const std::shared_ptr<Player>& player);
        void payRent(SideTile* tile, const std::shared_ptr<Player>& player);
        void buildHouse(SideTile* tile); 
        void buildHotel(SideTile* tile); 
        void move(const std::shared_ptr<Player>& player);
        bool isGameOver(void);
        void getFinalStandings();

        friend void gameLoop(Board board);
};

#endif