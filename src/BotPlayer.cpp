#include "BotPlayer.h"

bool BotPlayer::doAction(SideTile* tile){
    if (this->balance < tile->getPrice()) return false;
    return rand() % 4;
}