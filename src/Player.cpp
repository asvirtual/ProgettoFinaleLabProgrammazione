#include "Player.h"

void Player::deposit(int amount){
    this->balance += amount;
}

void Player::withdraw(int amount){
    this->balance -= amount;
}

int Player::throwDice(void){
    int roll;
    for (int i = 0; i < 2; i++)
        roll += (rand() % 6 + 1);

    return roll;
}
