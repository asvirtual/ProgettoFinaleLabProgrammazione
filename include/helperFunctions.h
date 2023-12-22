#include <iostream>
#include <string>

#include "Board.h"

class Board;

std::string getUserInput(std::string message);
char nthLetter(int idx);
void gameLoop(Board board);
void log(std::string message);