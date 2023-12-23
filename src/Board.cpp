#include <algorithm>
#include <iostream>
#include <string>

#include "Board.h"
#include "BotPlayer.h"
#include "monopoly.h"

Board::Board(const char* arg) {
    int economyCounter = 0, standardCounter = 0, luxuryCounter = 0;
    for (int i = 0; i < Board::TILES_COUNT; i++) {
        if (i % (Board::TILES_COUNT / 4) == 0) this->tiles.push_back(std::make_shared<CornerTile>(i));
        else {
            TileType tileType;
            switch (rand() % SideTile::TILES_TYPES_COUNT) {
                case 1:
                    if (luxuryCounter < Tile::LUXURY_COUNT) {
                        luxuryCounter++;
                        tileType = TileType::LUXURY;
                        break;
                    }
                case 2:
                    if (economyCounter < Tile::ECONOMY_COUNT) {
                        economyCounter++;
                        tileType = TileType::ECONOMY;
                        break;
                    }
                default:
                    standardCounter++;
                    tileType = TileType::STANDARD;
                    break;
            }

            this->tiles.push_back(std::make_shared<SideTile>(tileType, i));
        }
    }
    
    int startPosition = (rand() % 4) * (Board::TILES_COUNT / 4); // 0, 7, 14 or 21
    this->tiles[startPosition] = std::make_shared<CornerTile>(TileType::START, startPosition);

    std::string argumentAsString(arg);
    if (argumentAsString == "computer"){
        for (int i = 0; i < Board::PLAYERS_COUNT; i++) this->players.push_back(std::make_shared<BotPlayer>(startPosition));
    }
    else if (argumentAsString == "human"){
        this->players.push_back(std::make_shared<Player>(startPosition, PlayerType::HUMAN));
        for (int i = 0; i < Board::PLAYERS_COUNT-1; i++) this->players.push_back(std::make_shared<BotPlayer>(startPosition));
    }
}

void Board::print(void) {
    // 0 1 2 3 4 ... 27
    /*
        0  1  2  3  4  5  6  7
        27                   8
        26                   9
        25                   10
        24                   11
        23                   12
        22                   13
        21 20 19 18 17 16 15 14
    */
    std::cout << "   ";
    for (int i = 0; i < Board::SIDE_LENGTH; i++)
        std::cout << "     " << i;

    std::cout << "\n";

    for (int row = 0; row < Board::SIDE_LENGTH; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            if (col == 0) std::cout << " " << nthLetter(row) << "    ";
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1) {
                int idx = (row + col >= 2 * row) ? row + col : (Board::SIDE_LENGTH * 4 - 4) - (row + col);
                std::cout << "|" << this->tiles[idx]->toString(this->players) << "| ";
            } else
                std::cout << "      ";
        }

        std::cout << "\n";
    }

    std::cout << "\n";

    for (const std::shared_ptr<Player>& player : this->players) {
        std::cout << player->toString() << ": ";
        for (const std::shared_ptr<SideTile>& tile : player->ownedTiles) 
            std::cout << tile->position << " ";

        std::cout << "\n";
    }
    
    std::cout << "\n";
}

void Board::buyTerrain(SideTile* tile, const std::shared_ptr<Player>& player) {
    player->withdraw(tile->getTerrainPrice());
    tile->owner = player;
    player->ownedTiles.push_back(std::make_shared<SideTile>(tile->type, tile->position));
    log("Player " + std::to_string(player->id) + " has bought tile " + std::to_string(tile->position) + "!");
}

void Board::buildHouse(SideTile* tile) {
    tile->owner->withdraw(tile->getHousePrice());
    tile->building = TileBuilding::HOUSE;
    log("Player " + std::to_string(tile->owner->id) + " has built a house on tile " + std::to_string(tile->position) + "!");
}

void Board::buildHotel(SideTile* tile) {
    tile->owner->withdraw(tile->getHotelPrice());
    tile->building = TileBuilding::HOTEL;
    log("Player " + std::to_string(tile->owner->id) + " has built a hotel on tile " + std::to_string(tile->position) + "!");
}

void Board::payRent(SideTile* tile, const std::shared_ptr<Player>& player) {
    if (player->balance < tile->getRent()) {
        tile->owner->deposit(player->balance);
        for (const std::shared_ptr<SideTile>& tile : player->ownedTiles) {
            tile->owner = nullptr;
            tile->building = TileBuilding::NONE;
        }

        this->players.erase(
            std::find_if(
                this->players.begin(), this->players.end(),
                [player] (const std::shared_ptr<Player> p) { return p.get() == player.get(); }
            )
        );

        log("Player " + std::to_string(player->id) + " has been removed from the game!");
        return;
    } else {
        player->transfer(tile->getRent(), tile->owner);
        log("Player " + std::to_string(player->id) + " has paid " + std::to_string(tile->getRent()) + " fiorini to Player " + std::to_string(tile->owner->id) + " for rent at tile " + std::to_string(tile->position) + "!");
    }
}

void Board::move(const std::shared_ptr<Player>& player) {
    int roll = player->throwDice();

    for (int i = 1; i <= roll; i++){
        if(this->tiles[(player->position + i) % 28]->getType() == TileType::START){
            player->deposit(20);
            log("Player " + std::to_string(player->id) + " has passed by the start tile and received 20 fiorini!");
            break;
        }
    }

    player->position = (player->position + roll) % 28;
    log("Player " + std::to_string(player->id) + " has landed on tile " + std::to_string(player->position) + "!\n"); 

    if (this->tiles[player->position]->getType() == TileType::CORNER || this->tiles[player->position]->getType() == TileType::START)
        return;

    SideTile* tile = (SideTile*) this->tiles[player->position].get();
    if (tile->owner == nullptr && player->balance >= tile->getTerrainPrice()) {
        if (player->type == PlayerType::BOT) {
            BotPlayer* bot = (BotPlayer*) player.get();
            if (bot->getDecision()) this->buyTerrain(tile, player);
            return;
        }

        std::string answer = getUserInput("Do you want to buy this tile? (S/N) - show to print board ");
        if(answer == "show") this->print();
        if (answer == "S" || answer == "s") this->buyTerrain(tile, player);
    } else if (tile->owner == player) {
        if (
            (tile->building == TileBuilding::NONE && tile->getHousePrice() <= player->balance) ||
            (tile->building == TileBuilding::HOUSE && tile->getHotelPrice() <= player->balance)
        ) {
            if (player->type == PlayerType::BOT) {
                BotPlayer* bot = (BotPlayer*) player.get();
                if (bot->getDecision()) {
                    if (tile->building == TileBuilding::NONE) this->buildHouse(tile);
                    else this->buildHotel(tile);
                }
                return;
            }

            std::string question =  "Do you want to build a " + std::string(tile->building == TileBuilding::NONE ? "house" : "hotel") + "? (S/N) - show to print board ";
            std::string answer = getUserInput(question);
            if(answer == "show") this->print();
            if (answer == "S" || answer == "s") {
                if (tile->building == TileBuilding::NONE) this->buildHouse(tile);
                else this->buildHotel(tile);
            }
        }
    } else if (tile->owner != player)
        this->payRent(tile, player);
}

bool Board::isGameOver(void) {
    return this->players.size() == 1;
}

void Board::getFinalStandings(void) {
    std::sort(players.begin(), players.end(), [] (const std::shared_ptr<Player> p1, const std::shared_ptr<Player> p2) { return p1->getBalance() > p2->getBalance(); });
    std::vector<Player*> winners;

    bool isDraw = false;
    for (int i = 1; i < this->players.size() - 1; i++) {
        if (this->players[i]->balance == this->players[0]->balance) {
            winners.push_back(this->players[i].get());
            isDraw = true;
        }
    }

    std::cout << (isDraw ? "It's a draw!\n" : "The winner is " + (*players[0]).toString()) << "!\n";
    if (players.size() > 1) {
        int place = 0;
        for (const std::shared_ptr<Player>& p : this->players) {
            if (std::find(winners.begin(), winners.end(), p.get()) == winners.end()) place++;
            std::cout << place << ") Player: " << *p << "\n";
        }    
    }
}
