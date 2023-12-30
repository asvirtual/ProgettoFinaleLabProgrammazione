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
    This function gets the correct turn order of the players based on their dice roll at the beginning of the game.
    It takes a vector of pairs of pointers to players and their dice roll, and two iterators to the beginning and the end of a portion of the vector.
    The function will sort the players by their dice roll in non-increasing order and then, if there are players with the same dice roll
    the function will recursively call itself to sort the sub-portions of the vector containing the players with the same dice roll.
*/
void getTurnOrder(std::vector<playerRollPair>& rolls, std::vector<playerRollPair>::iterator begin, std::vector<playerRollPair>::iterator end) {
    // Throw the dice for each player
    for (auto it = begin; it != end; it++) it->second = it->first->throwDice();
    
    // Sort the players by their dice roll in non-increasing order
    std::sort(begin, end, [] (auto p1, auto p2) { return p1.second > p2.second; });
    
    // Check if there are players with the same dice roll and, if so, recursively call this function 
    // to sort the sub-portions of the vector containing the players with the same dice roll
    int portionSize = 0;
    for (auto it = begin; it != end; it++) {
        // Keep track of the number of players with the same dice roll
        if (it != end - 1 && it->second == (it + 1)->second) portionSize++; 

        // If we found a sub-portion of the vector containing players with the same dice roll and we reached its end (the next player has 
        // a different dice roll or the iterator points to the last element) sort the players in the said sub-portion of the vector
        if (portionSize > 0 && (it == end - 1 || it->second != (it + 1)->second)) {
            getTurnOrder(rolls, it - portionSize, it + 1);
            portionSize = 0;
        }
    }
}

/*
    This function sorts the players based on the dice roll at the beginning of the game.
    It uses the getTurnOrder function to sort the initialRolls vector by the players' dice roll 
    and then it sorts the actual board.players vector
*/
void sortPlayers(std::vector<std::shared_ptr<Player>>& players) {
    // Initialize the initialRolls vector, made of pairs of pointers to players and their 
    // dice roll, which we will then use to sort the actual board.players vector
    std::vector<playerRollPair> initialRolls;
    for (const std::shared_ptr<Player>& player: players) initialRolls.push_back(playerRollPair(player.get(), 0));

    getTurnOrder(initialRolls, initialRolls.begin(), initialRolls.end());

    // Sort the players vector based on the order found in initialRolls vector
    for (auto it = players.begin(); it != players.end(); it++) {
        // shared_ptr found in the current position of the players vector
        std::shared_ptr<Player>& current = *it; 
        // Pointer to the player found in the corresponding position of the initialRolls vector
        Player* correspondingPlayer = initialRolls[it - players.begin()].first; 

        // If the current player is already in the correct position, skip it
        if (*current.get() == *correspondingPlayer) continue;

        // Find the correct index for the "current" player, by finding the iterator pointing to the same player in the initialRolls vector
        auto toSwapIt = std::find_if(
            initialRolls.begin(), initialRolls.end(), 
            [it] (const playerRollPair& roll) { return *it->get() == *roll.first; }
        );
        int toSwapIdx = toSwapIt - initialRolls.begin();

        // Swap the pointer owned by the current shared_ptr with the pointer owned by the shared_ptr found at toSwapIdx
        current.swap(players[toSwapIdx]);
    }
}

void monopUtil::gameLoop(Board board) {
    sortPlayers(board.players);
    log("Ordine di gioco: ");
    for (const std::shared_ptr<Player>& player: board.getPlayers())
        monopUtil::log("Giocatore " + std::to_string(player->getId()));

    int turn = 0;
    board.print();

    // Main game loop, runs until the game is over or the maximum number of turns is reached
    while (!board.isGameOver() && turn < Board::MAX_TURNS) {
        turn++;
        for (const std::shared_ptr<Player>& player: board.getPlayers()) {
            if (player.get() == nullptr) continue; // Skip players that have lost and have been eliminated during this turn
            board.move(player); 
            monopUtil::log("Giocatore " + std::to_string(player->getId()) + " ha finito il turno");
        }
    }

    // Print the final standings and/or the winner
    board.getFinalStandings();
}

void monopUtil::log(std::string message) {
    std::cout << message << "\n";
    logFile << message << "\n";
}

void monopUtil::openLogFile(void) { logFile.open("log.txt"); }
void monopUtil::closeLogFile(void) { logFile.close(); }