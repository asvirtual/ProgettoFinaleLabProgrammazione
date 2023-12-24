// Author: Federico Zardo

#include "BotPlayer.h"

bool BotPlayer::getDecision() {
    return rand() % 4 == 0;
}