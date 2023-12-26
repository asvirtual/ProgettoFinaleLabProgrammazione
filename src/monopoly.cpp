// Author: Giordano Alberti

#include "monopoly.h"
#include <fstream>
#include <algorithm>

std::ofstream logFile;

char monopUtil::nthLetter(int idx)
{
    if (idx < 0 || idx > 20) return ' ';
    return "ABCDEFGHILMNOPQRSTUVZ"[idx];
}

bool monopUtil::compareRolls(const std::shared_ptr<Player>& p1, const std::shared_ptr<Player>& p2) {
    if(p1->getInitRoll() == p2->getInitRoll()){
        do{
            p1->newRoll();
            p2->newRoll();
        }while(p1->getInitRoll() == p2->getInitRoll());
    }
    return p1->getInitRoll() > p2->getInitRoll();
}

void monopUtil::gameLoop(Board board) {
    std::sort(board.players.begin(), board.players.end(), compareRolls); // Sorts the players by their dice roll
    int turn = 0;
    board.print();
    // Main game loop, runs until the game is over or the maximum number of turns is reached
    while (!board.isGameOver() && turn < Board::MAX_TURNS) {
        turn++;
        for (const std::shared_ptr<Player>& player: board.getPlayers()) {
            if (player.get() == nullptr) continue; // Skip players that have lost and have been eliminated during this turn
            board.move(player); 
            log("Giocatore " + std::to_string(player->getId()) + " ha finito il turno");
        }
    }

    // Print the final standings and/or the game winner
    board.getFinalStandings();
}

void monopUtil::log(std::string message) {
    std::cout << message << "\n";
    logFile << message << "\n";
}

void monopUtil::openLogFile(void) { logFile.open("log.txt"); }
void monopUtil::closeLogFile(void) { logFile.close(); }