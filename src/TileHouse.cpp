#include "TileHouse.h"

int TileHouse::getPrice(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 3;
        case TileType::STANDARD: return 5;
        case TileType::LUXURY: return 10;
        default: return 0;
    }
}

int TileHouse::getRent(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 2;
        case TileType::STANDARD: return 4;
        case TileType::LUXURY: return 7;
        default: return 0;
    }
} 