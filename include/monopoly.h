#include <iostream>
#include <string>

#include "Board.h"

    class Board;
namespace monopUtil{
    char nthLetter(int idx);
    void gameLoop(Board board);
    void openLogFile(void);
    void closeLogFile(void);
    void log(std::string message);
}