#include "SideTile.h"

SideTile::SideTile(TileType t, int p) : Tile(t, p) {
    switch (t) {
        case TileType::ECONOMY:
            this->housePrice = 3;
            this->hotelPrice = 3;
            break;
        case TileType::STANDARD:
            this->housePrice = 5;
            this->hotelPrice = 5;
            break;
        case TileType::LUXURY:
            this->housePrice = 10;
            this->hotelPrice = 10;
            break;
    }
};