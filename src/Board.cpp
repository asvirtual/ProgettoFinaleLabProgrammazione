// Author: Giordano Alberti

#include <algorithm>
#include <iostream>
#include <string>

#include "Board.h"
#include "BotPlayer.h"
#include "monopoly.h"

Board::Board(void) {
    monopUtil::openLogFile();
    this->generateTiles();
    this->generatePlayers();
}

Board::Board(bool humanPlayer) {
    monopUtil::openLogFile();
    this->humanPlayer = humanPlayer;
    this->generateTiles();
    this->generatePlayers();
}

void Board::generatePlayers(void) {
    int startPosition = this->getStartingPosition();
    // If called before generateTiles() throws an exception
    if (startPosition == -1) throw std::runtime_error("Couldn't generate players, starting position not found");
    
    if (this->humanPlayer) {
        this->players.push_back(std::make_shared<Player>(startPosition));
        for (int i = 0; i < Board::PLAYERS_COUNT - 1; i++) this->players.push_back(std::make_shared<BotPlayer>(startPosition));
    } else {
        for (int i = 0; i < Board::PLAYERS_COUNT; i++) this->players.push_back(std::make_shared<BotPlayer>(startPosition));
    }
}

void Board::generateTiles(void) {
    int economyCounter = 0, 
        standardCounter = 0, 
        luxuryCounter = 0;

    for (int i = 0; i < Board::TILES_COUNT; i++) {
        if (i % (Board::TILES_COUNT / 4) == 0) this->tiles.push_back(std::make_shared<CornerTile>(i));
        else {
            TileType tileType;
            // Generate a random tile type, but keep the number of tiles of each type under the maximum value by
            // only breaking the switch statement if the counter of the current tile type is under the maximum value
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
    
    // Randomly set the start tile
    int startPosition = (rand() % 4) * (Board::TILES_COUNT / 4);
    this->tiles[startPosition] = std::make_shared<CornerTile>(TileType::START, startPosition);
}

void Board::print(void) {
    /* If the board is printed as a matrix, the tiles' vector indexes are mapped to the matrix-like structure as follows:
        - if the tile is after the main diagonal (row + col >= 2 * row), the index is mapped to the sum of the row and column
        - if the tile is before the main diagonal (row + col < 2 * row), the index is mapped to the difference between the the number of tiles sum of the row and column

        0 1 2 3 4 ... 27

        0  1  2  3  4  5  6  7
        27 *                 8
        26    *              9
        25       *           10
        24          *        11
        23             *     12
        22                *  13
        21 20 19 18 17 16 15 14
    */
    std::cout << "\n   ";
    for (int i = 0; i < Board::SIDE_LENGTH; i++)
        std::cout << "     " << i + 1;

    std::cout << "\n";

    for (int row = 0; row < Board::SIDE_LENGTH; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            if (col == 0) std::cout << " " << monopUtil::nthLetter(row) << "    ";
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1) {
                // Map the row and column to the tiles' vector index (0..27)
                int idx = 
                    (row + col >= 2 * row) ? 
                    row + col : 
                    (Board::TILES_COUNT) - (row + col);

                std::cout << "|" << this->tiles[idx]->toString(this->players) << "| ";
            } else
                std::cout << "      "; // Inner spaces
        }

        std::cout << "\n";
    }

    std::cout << "\n";

    // Print players' owned tiles and balance
    for (const std::shared_ptr<Player>& player : this->players) {
        std::cout << player->toString() << ": ";
        for (const std::shared_ptr<SideTile>& tile : player->ownedTiles) 
            std::cout << tile->toCoordinates() << " ";

        std::cout << "\n";
    }
    
    std::cout << "\n";
}

int Board::getStartingPosition(void) {
    // If called before generateTiles() returns invalid position
    if (this->tiles.size() == 0) return -1;

    return std::find_if(
        this->tiles.begin(), this->tiles.end(),
        [] (const std::shared_ptr<Tile> tile) { return tile->getType() == TileType::START; }
    )->get()->position;
}

void Board::buyTerrain(SideTile* tile, const std::shared_ptr<Player>& player) {
    player->withdraw(tile->getTerrainPrice());
    player->ownedTiles.push_back(std::make_shared<SideTile>(*tile));
    tile->owner = player;
    monopUtil::log("Giocatore " + std::to_string(player->id) + " ha acquistato il terreno " + tile->toCoordinates());
}

void Board::buildHouse(SideTile* tile) {
    tile->owner->withdraw(tile->getHousePrice());
    tile->building = TileBuilding::HOUSE;
    monopUtil::log("Giocatore " + std::to_string(tile->owner->id) + " ha costruito una casa sul terreno " + tile->toCoordinates()); 
}

void Board::buildHotel(SideTile* tile) {
    tile->owner->withdraw(tile->getHotelPrice());
    tile->building = TileBuilding::HOTEL;
    monopUtil::log("Giocatore " + std::to_string(tile->owner->id) + " ha migliorato una casa in albergo sul terreno " + tile->toCoordinates());
}

void Board::payRent(SideTile* tile, const std::shared_ptr<Player>& player) {
    // If the player doesn't have enough money to pay the rent, he is eliminated
    if (player->balance < tile->getRent()) {
        monopUtil::log("Giocatore " + std::to_string(player->id) + " e' stato eliminato");
        // The owner gets all the player's money
        tile->owner->deposit(player->balance);
        // The player's owned tiles are freed and their buildings are reset
        for (const std::shared_ptr<SideTile>& ownedTile : player->ownedTiles) {
            ownedTile->owner = nullptr;
            ownedTile->building = TileBuilding::NONE;
        }

        this->players.erase(
            std::find_if(
                this->players.begin(), this->players.end(),
                [player] (const std::shared_ptr<Player>& p) { return p.get() == player.get(); }
            )
        );

        return;
    }

    player->transfer(tile->getRent(), tile->owner);
    monopUtil::log("Giocatore " + std::to_string(player->id) + " ha pagato " + std::to_string(tile->getRent()) + " fiorini al giocatore " + std::to_string(tile->owner->id) + " per pernottamento nella casella " + tile->toCoordinates());
}

void Board::move(const std::shared_ptr<Player>& player) {
    int roll = player->throwDice();

    // Check if the player's trajectory passes through the start tile
    for (int i = 1; i <= roll; i++){
        if (this->tiles[(player->position + i) % Board::TILES_COUNT]->getType() == TileType::START) {
            player->deposit(20);
            monopUtil::log("Giocatore " + std::to_string(player->id) + " e' passato dal via e ha ritirato 20 fiorini!");
            break;
        }
    }

    player->position = (player->position + roll) % Board::TILES_COUNT;
    monopUtil::log("Giocatore " + std::to_string(player->id) + " e' arrivato alla casella " + this->tiles[player->position]->toCoordinates());

    if (this->tiles[player->position]->getType() == TileType::CORNER || this->tiles[player->position]->getType() == TileType::START)
        return;

    // If the function hasn't returned, the tile is a SideTile, handle payments and buildings

    SideTile* tile = (SideTile*) this->tiles[player->position].get();
    if (tile->owner == nullptr && player->balance >= tile->getTerrainPrice()) {
        if (player->type == PlayerType::BOT) {
            BotPlayer* bot = (BotPlayer*) player.get();
            if (bot->getDecision()) this->buyTerrain(tile, player);

            return;
        }

        std::string answer = getUserInput("Vuoi comprare il terreno " + tile->toCoordinates() + "? (S/N) - show per visualizzare il tabellone ");
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

            std::string question =  "Vuoi costruire " + std::string(tile->building == TileBuilding::NONE ? "una casa" : "un albergo") + "? (S/N) - show per visualizzare il tabellone";
            std::string answer = getUserInput(question);
            if (answer == "S" || answer == "s") {
                if (tile->building == TileBuilding::NONE) this->buildHouse(tile);
                else this->buildHotel(tile);
            }
        }
    } else if (tile->owner != nullptr && tile->owner != player) 
        this->payRent(tile, player);
}

bool Board::isGameOver(void) {
    return this->players.size() == 1;
}

void Board::getFinalStandings(void) {
    std::vector<Player*> winners;
    std::sort(
        players.begin(), players.end(), 
        [] (const std::shared_ptr<Player> p1, const std::shared_ptr<Player> p2) { return p1->getBalance() > p2->getBalance(); }
    );

    // Check if there is a draw
    bool isDraw = false;
    for (int i = 1; i < this->players.size() - 1; i++) {
        if (this->players[i]->balance == this->players[0]->balance) {
            winners.push_back(this->players[i].get());
            isDraw = true;
            break;
        }
    }

    monopUtil::log(isDraw ? "Pareggio" : ("Giocatore " + std::to_string(players[0]->id) + " ha vinto la partita"));
    // If there is a draw or the game ended because it reached the maximum number of turns, print the players' rankings
    if (players.size() > 1) {
        int place = 0;
        for (const std::shared_ptr<Player>& p : this->players) {
            if (std::find(winners.begin(), winners.end(), p.get()) == winners.end()) place++;
            monopUtil::log(std::to_string(place) + ") " + (*p).toString());
        }    
    }
}

std::string Board::getUserInput(std::string message) {
    std::string answer;

    do {
        std::cout << message;
        std::cin >> answer;
        if (answer == "show") this->print();
    } while (answer != "S" && answer != "s" && answer != "N" && answer != "n");

    return answer;
}
