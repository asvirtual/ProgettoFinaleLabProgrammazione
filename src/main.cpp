#include "Board.h"
#include "CornerTile.h"
#include "TileTerrain.h"

#include <memory>
#include <vector>

int main(void) {
    srand(time(NULL));

    Board b = Board();
    b.print();
    
    return 0;
}