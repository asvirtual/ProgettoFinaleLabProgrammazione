// Author: Andrea Boscarin

#include <algorithm>

#include "SideTile.h"

int SideTile::getHotelPrice() {
    switch (this->type) {
        case TileType::ECONOMY:
            return 3;
        case TileType::STANDARD:
            return 5;
        case TileType::LUXURY:
            return 10;
        default:
            return -1;
    }
}

int SideTile::getHousePrice() {
    switch (this->type) {
        case TileType::ECONOMY:
            return 3;
        case TileType::STANDARD:
            return 5;
        case TileType::LUXURY:
            return 10;
        default:
            return -1;
    }
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
                default: return -1;
            }

        case TileBuilding::HOTEL:
            switch(this->type) {
                case TileType::ECONOMY: return 4;
                case TileType::STANDARD: return 8;
                case TileType::LUXURY: return 14;
                default: return -1;
            }

        default:
            return 0; // No building
    }
}

std::string SideTile::toString(const std::vector<std::shared_ptr<Player>>& players) const { 
    std::string toReturn;
    toReturn += (char) this->type;

    // Check if there is a building on the tile
    if (this->building == TileBuilding::HOUSE) toReturn += "*";
    else if (this->building == TileBuilding::HOTEL) toReturn += "^";
    else toReturn += " ";
    
    // Check if there is a player on the tile
    for (const std::shared_ptr<Player>& p : players) 
        if (p->getPosition() == this->position)
            toReturn += std::to_string(p->getId());

    // Pad the string with spaces to make it 3 characters long
    while (toReturn.length() < 3) toReturn += " ";
    return toReturn;
};
