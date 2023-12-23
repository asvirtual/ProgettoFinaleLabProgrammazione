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
    if (argc != 1 && (std::string(argv[1]) != "computer" && std::string(argv[1]) != "human")) {
        std::cerr << "Inserisci human per giocare contro 3 bot o computer per assistere a una partita tra 4 bot" << std::endl;
        throw std::invalid_argument("Invalid argument");
    }
        
    srand(time(0));

    Board b = Board(std::string(argv[1]) == "human");
    monopUtil::gameLoop(b);
    
    return 0;
}