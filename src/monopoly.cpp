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

void sortPlayers(std::vector<std::shared_ptr<Player>>& players, std::vector<std::shared_ptr<Player>>::iterator begin, std::vector<std::shared_ptr<Player>>::iterator end) {
    typedef std::pair<Player*, int> playerRollPair;
    std::vector<playerRollPair> rolls;

    for (auto it = begin; it != end; it++) {
        std::cout << "Player " << (*it)->getId() << " rolling dice \n";
        rolls.push_back(playerRollPair(it->get(), (*it)->throwDice()));
    }
    
    std::sort(begin, end, [rolls] (auto p1, auto p2) { 
        return (
            std::find_if(rolls.begin(), rolls.end(), [p1] (auto pair) { return *pair.first == *p1; })->second > 
            std::find_if(rolls.begin(), rolls.end(), [p2] (auto pair) { return *pair.first == *p2; })->second
        );
    });

    std::sort(rolls.begin(), rolls.end(), [] (auto p1, auto p2) { return p1.second > p2.second; });

    for (const std::shared_ptr<Player>& player: players)
        monopUtil::log("Giocatore " + std::to_string(player->getId()));
    
    std::cout << "\n";
    
    int notSortedPortion = 0;
    for (int i = 1; i < rolls.size(); i++) {
        if (rolls[i].second == rolls[i - 1].second) notSortedPortion++;
        if (notSortedPortion > 0 && (rolls[i].second != rolls[i - 1].second || i == rolls.size() - 1)) {
            sortPlayers(players, players.begin() + i - notSortedPortion, players.begin() + i);
            notSortedPortion = 0;
        }
    }
}

void monopUtil::gameLoop(Board board) {
    std::vector<int> rolls;
    sortPlayers(board.players, board.players.begin(), board.players.end());

    for (const std::shared_ptr<Player>& player: board.getPlayers())
        log("Giocatore " + std::to_string(player->getId()));

    return;
    
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