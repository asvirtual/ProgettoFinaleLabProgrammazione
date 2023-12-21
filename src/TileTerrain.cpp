#include "TileTerrain.h"

int TileTerrain::getPrice(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 6;
        case TileType::STANDARD: return 10;
        case TileType::LUXURY: return 20;
        default: return 0;
    }
}