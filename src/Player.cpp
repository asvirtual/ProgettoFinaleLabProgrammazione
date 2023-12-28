#include "Player.h"
#include "monopoly.h"

void Player::deposit(int amount) {
    this->balance += amount;
}

void Player::withdraw(int amount) {
    this->balance -= amount;
}

void Player::transfer(int amount, const std::shared_ptr<Player>& player) {
    this->withdraw(amount);
    player->deposit(amount);
}

int Player::throwDice(void) {
    int roll = 0;
    for (int i = 0; i < 2; i++)
        roll += ((rand() % 6) + 1);

    monopUtil::log("Giocatore " + std::to_string(this->id) + " ha tirato i dadi ottenendo un valore di " + std::to_string(roll));
    return roll;
}

void Player::newRoll(void){
    this->initRoll = this->throwDice();
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    return os << p.toString();    
}

