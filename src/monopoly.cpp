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

    for (std::shared_ptr<Player> player: board.getPlayers()) {
        int roll = player->throwDice();
        if (roll > max) {
            max = roll;
            firstPlayerIdx = player->getId();
        }
    }

    std::swap(board.players[0], board.players[firstPlayerIdx]);

    int turn = 0;
    board.print();
    while (!board.isGameOver() && turn < Board::MAX_TURNS) {
        turn++;
        for (const std::shared_ptr<Player>& player: board.getPlayers()) {
            if (player.get() == nullptr) continue;
            board.move(player);
            log("Giocatore " + std::to_string(player->getId()) + " ha finito il turno");
        }
    }

    board.getFinalStandings();
}

void monopUtil::log(std::string message) {
    std::cout << message << "\n";
    logFile << message << "\n";
}

void monopUtil::openLogFile(void) { logFile.open("log.txt"); }
void monopUtil::closeLogFile(void) { logFile.close(); }