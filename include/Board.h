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
#include "monopoly.h"

class Board {
    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Player>> players;
        const char* commArg;

    public:
        static constexpr int SIDE_LENGTH = 8;
        static constexpr int TILES_COUNT = 28;
        static constexpr int PLAYERS_COUNT = 4;
        static constexpr int MAX_TURNS = 100;
        
        Board(const char* arg);
        ~Board(void) { closeLogFile(); };
        const std::vector<std::shared_ptr<Player>>& getPlayers(void) const { return this->players; };
        void print(void);
        void buyTerrain(SideTile* tile, const std::shared_ptr<Player>& player);
        void payRent(SideTile* tile, const std::shared_ptr<Player>& player);
        void buildHouse(SideTile* tile); 
        void buildHotel(SideTile* tile); 
        void move(const std::shared_ptr<Player>& player);
        bool isGameOver(void);
        void getFinalStandings();
        std::string getUserInput(std::string message);

        friend void gameLoop(Board board);
};

#endif