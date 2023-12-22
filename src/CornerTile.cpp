#include <vector>
#include <string>
#include <memory>

#include "Player.h"
#include "CornerTile.h"

std::string CornerTile::toString(std::vector<std::shared_ptr<Player>>& players) const { 
    std::string toReturn;
    toReturn += (char) this->type;
    
    for (std::shared_ptr<Player> p : players) {
        if (p->getPosition() == this->position) {
            toReturn += std::to_string(p->getId());
            break;
        }
    }

    return toReturn;
};
