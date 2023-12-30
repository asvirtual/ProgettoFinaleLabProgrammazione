// Author: Giordano Alberti

#include "monopoly.h"
#include <fstream>
#include <algorithm>

std::ofstream logFile;

char monopolyUtil::nthLetter(int idx)
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
        auto next = it + 1;
        // Keep track of the number of players with the same dice roll
        if (it != end - 1 && it->second == next->second) portionSize++; 

        // If we found a sub-portion of the vector containing players with the same dice roll and we reached its end (the next player has 
        // a different dice roll or the iterator points to the last element) sort the players in the said sub-portion of the vector
        if (portionSize > 0 && (next == end || it->second != next->second)) {
            getTurnOrder(rolls, it - portionSize, next);
            portionSize = 0;
        }
    }
}

/*
    This function sorts the players based on the dice roll at the beginning of the game.
    It uses the getTurnOrder function to sort the initialRolls vector by the players' dice roll 
    and then it copies that order in the actual board.players vector, which is passwed as a parameter.
*/
void sortPlayers(std::vector<std::shared_ptr<Player>>& players) {
    // Initialize the initialRolls vector, made of pairs of pointers to players and their 
    // dice roll, which we will then use to sort the actual board.players vector
    std::vector<playerRollPair> initialRolls;
    for (const std::shared_ptr<Player>& player: players) initialRolls.push_back(playerRollPair(player.get(), 0));

    getTurnOrder(initialRolls, initialRolls.begin(), initialRolls.end());

    // Sort the players vector copying the order found in initialRolls vector
    std::sort(
        players.begin(), players.end(), 
        [initialRolls] (std::shared_ptr<Player>& p1, std::shared_ptr<Player>& p2) {
            return 
                // Sort p1 and p2 based on which one comes first (has the lower index) in the initialRolls vector
                (std::find_if(initialRolls.begin(), initialRolls.end(), [p1] (playerRollPair p) { return *p.first == *p1; }) - initialRolls.begin()) < 
                (std::find_if(initialRolls.begin(), initialRolls.end(), [p2] (playerRollPair p) { return *p.first == *p2; }) - initialRolls.begin());
        }
    );
}

void monopolyUtil::gameLoop(Board board) {
    sortPlayers(board.players);
    log("Ordine di gioco: ");
    for (const std::shared_ptr<Player>& player: board.getPlayers())
        monopolyUtil::log("Giocatore " + std::to_string(player->getId()));

    int turn = 0;
    board.print();

    // Main game loop, runs until the game is over or the maximum number of turns is reached
    while (!board.isGameOver() && turn < Board::MAX_TURNS) {
        turn++;
        for (const std::shared_ptr<Player>& player: board.getPlayers()) {
            if (player.get() == nullptr) continue; // Skip players that have lost and have been eliminated during this turn
            board.move(player);
            monopolyUtil::log("Giocatore " + std::to_string(player->getId()) + " ha finito il turno");
        }
    }

    // Print the final standings and/or the winner
    board.getFinalStandings();
}

void monopolyUtil::log(std::string message) {
    std::cout << message << "\n";
    logFile << message << "\n";
}

void monopolyUtil::openLogFile(void) { logFile.open("log.txt"); }
void monopolyUtil::closeLogFile(void) { logFile.close(); }