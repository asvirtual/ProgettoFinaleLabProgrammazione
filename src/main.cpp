#include "Board.h"
#include "helperFunctions.h"

#include <memory>
#include <vector>

int main(void) {
    srand(time(0));
        
    Board b = Board();
    b.print();

    gameLoop(b);
    
    return 0;
}