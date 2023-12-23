#include "Board.h"
#include "monopoly.h"

#include <memory>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    srand(time(0));

    if (argc != 1 && (std::string(argv[1]) != "computer" && std::string(argv[1]) != "human")) {
        std::cout <<"Inserisci human per giocare contro 3 bot o computer per guardare una partita tra 4 bot" << std::endl;
        throw std::invalid_argument("Invalid argument");
    }
        
    Board b = Board(argv[1]);
    b.print();

    gameLoop(b);
    
    return 0;
}