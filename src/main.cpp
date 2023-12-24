/*  ##################################################################
    # Progetto finale "Laboratorio di Programmazione C++ - Monopoly" #
    #           A.A. 2023-2034 - Gruppo Riferimenti& Confusi         #
    #                                                                #
    #         Giordano Alberti, Andrea Boscarin, Federico Zardo      #
    #                                                                #                    
    ##################################################################
*/
#include "Board.h"
#include "monopoly.h"

#include <memory>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    // Check if the user has provided a valid argument
    if (argc != 2 || ((std::string(argv[1]) != "computer" && std::string(argv[1]) != "human"))) {
        std::cerr << "Inserisci human per giocare contro 3 bot o computer per assistere a una partita tra 4 bot" << std::endl;
        return 1;
    }
        
    srand(time(0)); // Seed the random number generator once, it will be used by BotPlayer objects

    Board b = Board(argv[1] == "human");
    monopUtil::gameLoop(b);
    
    return 0;
}