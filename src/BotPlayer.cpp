#include "BotPlayer.h"

bool BotPlayer::buyTile(SideTile* tile){
    if (this->balance < tile->getPrice()) return false;
    return rand() % 2;
}