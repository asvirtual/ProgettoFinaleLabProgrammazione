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

/*
    This function sorts the players by their dice roll at the beginning of the game.
    It takes a vector of pairs of pointers to players and their dice roll, and two iterators to the beginning and the end of a portion of the vector.
    The function will sort the players by their dice roll in non-increasing order and then, if there are players with the same dice roll
    the function will recursively call itself to sort the sub-portion of the vector containing the players with the same dice roll.
*/
void monopUtil::sortPlayers(std::vector<playerRollPair>& rolls, std::vector<playerRollPair>::iterator begin, std::vector<playerRollPair>::iterator end) {
    std::cout << "Sorting portion: [ ";
    for (auto it = begin; it != end; it++) {
        std::cout << std::to_string(it->first->getId()) << ", ";
    }

    std::cout << "]\n";

    // Throw the dice for each player
    for (auto it = begin; it != end; it++) it->second = it->first->throwDice();
    
    // Sort the players by their dice roll in non-increasing order (if p1 is greater or equal than p2, p1 will be placed before p2)
    std::sort(begin, end, [] (auto p1, auto p2) { return p1.second > p2.second; });

    // Print the temporary player order
    std::cout << "[ ";
    for (const playerRollPair& roll: rolls)
        std::cout << "(" << std::to_string(roll.first->getId()) << ", " << std::to_string(roll.second) << ")" << ", ";
    
    std::cout << "]\n";
    
    // Check if there are players with the same dice roll and, if so, keep track of the number of players with the same dice roll
    // and recursively call this function to sort the sub-portions of the vector containing the players with the same dice roll
    int nonSortedPortion = 0;
    for (auto it = begin; it != end; it++) {
        // Keep track of the number of players with the same dice roll
        if (it != end - 1 && it->second == (it + 1)->second) nonSortedPortion++; 

        // If we found a portion of the vector containing players with the same dice roll and we reached its end (the next player has 
        // a different dice roll or the iterator points to the last element) sort the players in the said portion of the vector
        if (nonSortedPortion > 0 && (it == end - 1 || it->second != (it + 1)->second)) {
            sortPlayers(rolls, it - nonSortedPortion, it + 1);
            nonSortedPortion = 0;
        }
    }
}

void monopUtil::gameLoop(Board board) {
    // Initialize the rolls vector, made of pairs of pointers to players and their 
    // dice roll, which we will then use to sort the actual board.players vector
    std::vector<playerRollPair> rolls;
    for (const std::shared_ptr<Player>& player: board.getPlayers())
        rolls.push_back(playerRollPair(player.get(), 0));

    sortPlayers(rolls, rolls.begin(), rolls.end());

    // Sort the players vector based on the roll vector, by finding the dice roll of each player in the roll vector
    for (auto it = rolls.begin(); it != rolls.end(); it++) {
        auto toSwapIt = std::find_if(
            board.players.begin(), board.players.end(),
            [it] (const std::shared_ptr<Player>& p) { return *p == *it->first; }
        );

        std::swap(board.players[it - rolls.begin()], board.players[toSwapIt - board.players.begin()]);
    }

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