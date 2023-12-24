#include "monopoly.h"
#include <fstream>

std::ofstream logFile;

char monopUtil::nthLetter(int idx)
{
    if (idx < 0 || idx > 20) return ' ';
    return "ABCDEFGHILMNOPQRSTUVZ"[idx];
}

void monopUtil::gameLoop(Board board) {
    int max;
    int firstPlayerIdx = 0;

    // Determine the starting player based on the highest dice roll
    for (std::shared_ptr<Player> player: board.getPlayers()) {
        int roll = player->throwDice();
        if (roll > max) {
            max = roll;
            firstPlayerIdx = player->getId();
        }
    }

    std::swap(board.players[0], board.players[firstPlayerIdx]); // Swap the first player with the starting player

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