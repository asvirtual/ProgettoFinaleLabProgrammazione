#include "helperFunctions.h"

char nthLetter(int idx)
{
    if (idx < 0 || idx > 20) return ' ';
    return "ABCDEFGHILMNOPQRSTUVZ"[idx];
}

std::string getUserInput(std::string message) {
    std::string answer;

    do {
        std::cout << message;
        std::cin >> answer;
    } while (answer != "S" && answer != "s" && answer != "N" && answer != "n" && answer != "show");

    return answer;
}

void gameLoop(Board board) {
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
    while (!board.isGameOver() && turn < Board::MAX_TURNS) {
        turn++;
        std::cout << "New turn!" << turn << "\n";
        for (const std::shared_ptr<Player>& player: board.getPlayers()) {
            if (player.get() == nullptr) continue;
            board.move(player);
            log("Player " + std::to_string(player->getId()) + " has ended his turn" + "!\n");
            board.print();
        }
    }

    std::cout << "End of the game!\n";
    board.getFinalStandings();
}

void log(std::string message) {
    std::cout << message << "\n";
}