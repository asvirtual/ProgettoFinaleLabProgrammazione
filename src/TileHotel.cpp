#include "TileHotel.h"

int TileHotel::getPrice(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 3;
        case TileType::STANDARD: return 5;
        case TileType::LUXURY: return 10;
        default: return 0;
    }
}

int TileHotel::getRent(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 4;
        case TileType::STANDARD: return 8;
        case TileType::LUXURY: return 14;
        default: return 0;
    }
}