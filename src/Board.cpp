#include "Board.h"
#include <iostream>

void Board::print(void) {
    /*
        0 1 2 3 4 5 6 0
        6             1
        5             2
        4             3
        3             4
        2             5
        1             6
        0 6 5 4 3 2 1 0
    */

    // 0, 0 -> 0
    // 0, 1 -> 1
    // ..
    // 0, 7 -> 7
    // 1, 0 -> 8
    // 1, 1 -> none
    // ..
    // 1, 7 -> 9
    // 2, 0 -> 10
    // ..
    // 7, 7 -> 27


    for (int i = 0; i < Board::SIDE_LENGTH; i++) {
        for (int j = 0; j < Board::SIDE_LENGTH; j++) {
            if (j == 0 || j == Board::SIDE_LENGTH - 1 || i == 0 || i == Board::SIDE_LENGTH - 1) {
                int idx = i + (j - 7) % 7;
                std::cout << "|" << (char) (this->tiles[idx]->getType()) << "| ";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << "\n";
    }
}