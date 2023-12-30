// Author: Federico Zardo

#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include <random>

#include "Player.h"
#include "SideTile.h"

/*
    BotPlayer class which represents a bot player of the game.
    It inherits from the Player class and it adds the getDecision() method
    to simulate the bot's decision (buy a terrain, build a house or a hotel...)
    with a positive outcome with 25% probability
*/
class BotPlayer : public Player {
    public:
        BotPlayer(void) : Player() {};
        BotPlayer(int p) : Player(p, PlayerType::BOT) {};
        bool getDecision();
};

#endif