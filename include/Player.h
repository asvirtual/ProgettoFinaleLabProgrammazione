#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <memory>
#include <iostream>

// #include "Tile.h"
// #include "SideTile.h"
// #include "TileTerrain.h"
// #include "TileHouse.h"

enum class PlayerType {
    HUMAN,
    BOT
};

class SideTile;

class Player {
    protected:
        static constexpr int STARTING_BALANCE = 100;
        static inline int playersCounter;
        int balance;
        int position;
        int id;
        PlayerType type;
        std::vector<std::shared_ptr<SideTile>> ownedTiles;

    public:
        Player(void) : balance(STARTING_BALANCE), id(playersCounter++), position(0), type(PlayerType::BOT) {};
        Player(int p) : balance(STARTING_BALANCE), id(playersCounter++), position(p), type(PlayerType::HUMAN) {};
        Player(int p, PlayerType t) : balance(STARTING_BALANCE), id(playersCounter++), position(p), type(t) {};
        
        void print(void) {};
        int getBalance(void) const { return this->balance; };
        int getId(void) const { return this->id; };
        int getPosition(void) const { return this->position; };
        void deposit(int amount);
        void withdraw(int amount);
        void transfer(int amount, const std::shared_ptr<Player>& player);
        int throwDice(void);
        bool operator==(const Player& p) const { return this->id == p.id; };
        std::string toString(void) const { return "Giocatore " + std::to_string(this->id) + " - " + std::to_string(this->balance) + " fiorini"; };
        friend class Board;
};

std::ostream& operator<<(std::ostream& os, const Player& p);

#endif