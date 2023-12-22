#ifndef BOTPLAYER_H
#define BOTPLAYER_H

#include <random>

#include "Player.h"
#include "SideTile.h"

class BotPlayer : public Player {
    public:
        BotPlayer(void) : Player() {};
        BotPlayer(int p) : Player(p, PlayerType::BOT) {};
        bool getDecision();
};

#endif