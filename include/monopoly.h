// Author: Giordano Alberti

#include <iostream>
#include <string>

#include "Board.h"

class Board; // Forward declaration

// This type will be used to sort the players by their dice roll at the beginning of the game
typedef std::pair<Player*, int> playerRollPair; 

/*
    The monopolyUtil namespace contains utility functions for the game.
*/
namespace monopolyUtil {
    char nthLetter(int idx);
    void gameLoop(Board board); // Main game loop, determines the starting player and runs the game
    void openLogFile(void);
    void closeLogFile(void);
    void log(std::string message); // Prints a message to the console and to the log file
}