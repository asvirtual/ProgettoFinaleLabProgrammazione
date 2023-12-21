#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <random>
#include <ctime>
#include <memory>

#include "Tile.h"

class Player {
    protected:
        int balance;
        int position;
        int id;
        std::vector<std::shared_ptr<Tile>> ownedTiles;

    public:
        Player(void) {};
        Player(int b, int p, int id) : balance(b), position(p), id(id) {};
        
        void print(void) {};
        int getBalance(void) const { return this->balance; };
        int getId(void) const { return this->id; };
        void deposit(int amount);
        void withdraw(int amount);
        int throwDice(void);
};

#endif