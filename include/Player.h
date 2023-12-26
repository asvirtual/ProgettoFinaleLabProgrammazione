// Author: Andrea Boscarin

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <memory>
#include <iostream>

/*
    Player class which represents a player of the game.
    It contains the player's balance, position, id and type (human or bot), and provides
    some member function to handle the player's balance and simulate the dice roll
*/
enum class PlayerType {
    HUMAN,
    BOT
};

class SideTile; // Forward declaration

class Player {
    protected:
        static constexpr int STARTING_BALANCE = 100;
        static inline int playersCounter; // Static counter to keep track of the number of players created and assign the ids
        int balance;
        int position;
        int id;
        int initRoll; // Stores the result of the dice roll at the beginning of the game
        PlayerType type;
        std::vector<std::shared_ptr<SideTile>> ownedTiles; // Vector of pointers to the tiles owned by the player

    public:
        // Default constructor, creates a bot player without knowing the board's starting position
        Player(void) : balance(STARTING_BALANCE), id(playersCounter++), position(0), type(PlayerType::BOT), initRoll(this->throwDice()) {}; 
        // Creates a human player knowing the board's starting position
        Player(int p) : balance(STARTING_BALANCE), id(playersCounter++), position(p), type(PlayerType::HUMAN), initRoll(this->throwDice()) {};
        // Creates a player knowing the board's starting position and the type of the player (human or bot)
        Player(int p, PlayerType t) : balance(STARTING_BALANCE), id(playersCounter++), position(p), type(t), initRoll(this->throwDice()) {};
        
        int getBalance(void) const { return this->balance; };
        int getId(void) const { return this->id; };
        int getPosition(void) const { return this->position; };
        int getInitRoll(void) const { return this->initRoll; };
        void newRoll(void);
        void deposit(int amount);
        void withdraw(int amount);
        void transfer(int amount, const std::shared_ptr<Player>& player); // Transfers an amount of money from the instance player to another player
        int throwDice(void); // Simulates the dice roll and returns the result
        bool operator==(const Player& p) const { return this->id == p.id; }; // Overloads the == operator to compare two players by their id
        std::string toString(void) const { return "Giocatore " + std::to_string(this->id) + " - " + std::to_string(this->balance) + " fiorini"; };
        friend class Board; // Board class needs to access the player's position to move it and ownedTiles to handle the player's elimination
};

std::ostream& operator<<(std::ostream& os, const Player& p);

#endif