#include "BotPlayer.h"

bool BotPlayer::wantsToBuy(SideTile* tile){
    if (this->balance < tile->getPrice()) return false;
    return rand() % 4;
}