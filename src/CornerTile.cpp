// Author: Giordano Alberti

#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "CornerTile.h"

std::string CornerTile::toString(const std::vector<std::shared_ptr<Player>>& players) const { 
    std::string toReturn;
    toReturn += (char) this->type;
    
    // Check if there is a player on the tile
    for (const std::shared_ptr<Player>& p : players) {
        if (p->getPosition() == this->position) {
            toReturn += std::to_string(p->getId());
            break;
        }
    }

    // Pad the string with spaces to make it 3 characters long
    while (toReturn.length() < 3) toReturn += " ";
    return toReturn;
};
