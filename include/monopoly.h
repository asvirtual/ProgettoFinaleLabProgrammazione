// Author: Giordano Alberti

#include <iostream>
#include <string>

#include "Board.h"

class Board; // Forward declaration

/*
    monopUtil namespace which contains utility functions for the game.
*/
namespace monopUtil{
    char nthLetter(int idx);
    void gameLoop(Board board); // Main game loop, determines the starting player and runs the game
    void openLogFile(void);
    void closeLogFile(void);
    void log(std::string message); // Prints a message to the console and to the log file
    bool compareRolls(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2); // Compares the dice rolls of two players and returns true if p1 has a higher roll than p2 
}