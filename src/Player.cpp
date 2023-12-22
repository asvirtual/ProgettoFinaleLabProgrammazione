#include "Player.h"
#include "helperFunctions.h"

void Player::deposit(int amount){
    this->balance += amount;
}

void Player::withdraw(int amount){
    this->balance -= amount;
}

void Player::transfer(int amount, std::shared_ptr<Player> player) {
    this->balance -= amount;
    player->balance += amount;
}

int Player::throwDice(void) {
    int roll = 0;
    for (int i = 0; i < 2; i++) {
        roll += ((rand() % 6) + 1);
    }

    log("Player " + std::to_string(this->id) + " rolled " + std::to_string(roll) + "!\n");
    return roll;
}

std::ostream& operator<<(std::ostream& os, const Player& p) {
    return os << "Player " << p.getId() << " with balance: fiorini" << p.getBalance() << "\n";    
}

