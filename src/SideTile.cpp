#include "SideTile.h"

int SideTile::getHotelPrice() {
    switch (this->type) {
        case TileType::ECONOMY:
            return 3;
        case TileType::STANDARD:
            return 5;
        case TileType::LUXURY:
            return 10;
    }

    return -1;
}

int SideTile::getHousePrice() {
    switch (this->type) {
        case TileType::ECONOMY:
            return 3;
        case TileType::STANDARD:
            return 5;
        case TileType::LUXURY:
            return 10;
    }

    return -1;
}

int SideTile::getTerrainPrice(void) {
    switch(this->type) {
        case TileType::ECONOMY: return 6;
        case TileType::STANDARD: return 10;
        case TileType::LUXURY: return 20;
        default: return -1;
    }
}

int SideTile::getRent(void) {
    switch (this->building) {
        case TileBuilding::HOUSE:
            switch(this->type) {
                case TileType::ECONOMY: return 2;
                case TileType::STANDARD: return 4;
                case TileType::LUXURY: return 7;
                default: return 0;
            }

        case TileBuilding::HOTEL:
            switch(this->type) {
            case TileType::ECONOMY: return 4;
            case TileType::STANDARD: return 8;
            case TileType::LUXURY: return 14;
            default: return 0;
        }
    }

    return 0;
}