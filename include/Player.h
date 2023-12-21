#ifndef PLAYER_H
#define PLAYER_H

#include "Tile.h"
#include <vector>
#include <random>
#include <ctime>

class Player {
    protected:
        int balance;
        int position;
        char id;
        std::vector <Tile*> ownedTiles;
        

    public:
        Player(void) {};
        Player(int amount, int pos, char idnum);
        
        void print(void) {};
        int getBalance(void) const { return this->balance; };
        char getId(void) const { return this->id; };
        void deposit(int amount);
        void withdraw(int amount);
        int throwDice(void);

};

#endif