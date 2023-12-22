#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <random>
#include <ctime>
#include <memory>

#include "Tile.h"
#include "SideTile.h"
#include "TileTerrain.h"
#include "TileHouse.h"

class Player {
    protected:
        static int PLAYERS_COUNTER;
        int balance;
        int position;
        int id;
        PlayerType type;
        std::vector<std::shared_ptr<SideTile>> ownedTiles;

    public:
        Player(void) : balance(100), position(0), id(PLAYERS_COUNTER++), type(PlayerType::BOT) {};
        Player(int b, int p, PlayerType t) : balance(100), position(p), id(PLAYERS_COUNTER++), type(t) {};
        
        void print(void) {};
        int getBalance(void) const { return this->balance; };
        int getId(void) const { return this->id; };
        void deposit(int amount);
        void withdraw(int amount);
        void transfer(int amount, std::shared_ptr<Player> player);
        int throwDice(void);
        bool canBuy(SideTile* tile) const { return this->balance >= tile->getPrice(); };
        bool canPayRent(SideTile* tile) const { return this->balance >= tile->getRent(); };
        bool canBuildHouse(TileTerrain* tile) const { return this->balance >= tile->getHousePrice(); };
        bool canBuildHotel(TileHouse* tile) const { return this->balance >= tile->getHotelPrice(); };
        bool operator==(const Player& p) const { return this->id == p.id; };
        friend class Board;
};

enum class PlayerType {
    HUMAN,
    BOT
};

#endif