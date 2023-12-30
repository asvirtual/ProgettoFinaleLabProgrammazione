// Author: Giordano Alberti

#include <iostream>
#include <string>

#include "Board.h"

class Board; // Forward declaration

/*
    monopUtil namespace which contains utility functions for the game.
*/

// This type will be used to sort the players by their dice roll at the beginning of the game
typedef std::pair<Player*, int> playerRollPair; 

namespace monopUtil{
    char nthLetter(int idx);
    // Sorts the players by their dice roll at the beginning of the game
    void sortPlayers(std::vector<playerRollPair>& rolls, std::vector<playerRollPair>::iterator begin, std::vector<playerRollPair>::iterator end);
    void gameLoop(Board board); // Main game loop, determines the starting player and runs the game
    void openLogFile(void);
    void closeLogFile(void);
    void log(std::string message); // Prints a message to the console and to the log file
}