#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "CornerTile.h"

std::string CornerTile::toString(const std::vector<std::shared_ptr<Player>>& players) const { 
    std::string toReturn;
    toReturn += (char) this->type;
    
    for (const std::shared_ptr<Player>& p : players) {
        if (p->getPosition() == this->position) {
            toReturn += std::to_string(p->getId());
            break;
        }
    }

    if (toReturn.length() == 1) toReturn += "  ";
    if (toReturn.length() == 2) toReturn += " ";

    return toReturn;
};
