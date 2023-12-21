#include "Player.h"

Player::Player(int amount, int pos, char idnum){
    this->balance = amount;
    this->position = pos;
    this->id = idnum;
}

Player::Player(const Player& other){
    this->balance = other.balance;
    this->position = other.position;
    this->id = other.id;
}

void Player::deposit(int amount){
    this->balance += amount;
}

void Player::withdraw(int amount){
    this->balance -= amount;
}

int Player::throwDice(void){
    int roll;
    srand(time(0));
    for(int i = 0; i < 2; i++)
        roll+= (rand() % 6 + 1);
    return roll;

}

Player& Player::operator=(const Player& other){
    this->balance = other.balance;
    this->position = other.position;
    this->id = other.id;

    return *this;
}