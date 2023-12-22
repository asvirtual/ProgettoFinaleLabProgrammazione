#include <algorithm>
#include <iostream>

#include "Board.h"

char nthLetter(int idx)
{
    if (idx < 0 || idx > 20) return ' ';
    return "ABCDEFGHILMNOPQRSTUVZ"[idx];
}

Board::Board(void) {
    int economyCounter = 0, standardCounter = 0, luxuryCounter = 0;
    for (int i = 0; i < 28; i++) {
        if (i % 7 == 0) this->tiles.push_back(std::make_shared<CornerTile>(i));
        else {
            TileType tileType;
            switch (rand() % 3) {
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

            this->tiles.push_back(std::make_shared<TileTerrain>(tileType, i));
        }
    }
    
    int startPosition = (rand() % 4) * 7; // 0, 7, 14 or 21
    this->tiles[startPosition] = std::make_shared<CornerTile>(TileType::START, startPosition);
    for (int i = 0; i < Board::PLAYERS_COUNT; i++) this->players.push_back(std::make_shared<BotPlayer>(0, startPosition));
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
    std::cout << "    ";
    for (int i = 0; i < Board::SIDE_LENGTH; i++)
        std::cout << "   " << i;

    std::cout << "\n";

    for (int row = 0; row < Board::SIDE_LENGTH; row++) {
        for (int col = 0; col < Board::SIDE_LENGTH; col++) {
            if (col == 0) std::cout << " " << nthLetter(row) << "    ";
            if (row == 0 || row == Board::SIDE_LENGTH - 1 || col == 0 || col == Board::SIDE_LENGTH - 1) {
                int idx = (row + col >= 2 * row) ? row + col : (Board::SIDE_LENGTH * 4 - 4) - (row + col);
                std::cout << "|" << (char) this->tiles[idx]->type << "| ";
            } else
                std::cout << "    ";
        }
        std::cout << "\n";
    }
}

void Board::buyTerrain(SideTile* tile, std::shared_ptr<Player> player) {    
    if (player->balance < tile->getPrice()) return;
    player->withdraw(tile->getPrice());
    tile->owner = player;
}

/* TODO */
void Board::buildHouse(TileTerrain* tile) {
    
}

/* TODO */
void Board::buildHotel(TileHouse* tile) {
    
}

void Board::payRent(SideTile* tile, std::shared_ptr<Player> player) {    
    if (tile->owner == nullptr || tile->owner == player) return;

    if (player->balance < tile->getRent()) {
        std::cout << "Player " << player->id << " is bankrupt!\n";
        tile->owner->deposit(player->balance);
        for (std::shared_ptr<SideTile> tile : player->ownedTiles)
            this->tiles[tile->position] = std::make_shared<TileTerrain>(tile->type, tile->position);

        this->players.erase(
            std::find_if(
                this->players.begin(), this->players.end(), 
                [player] (std::shared_ptr<Player> const& p) { return p.get() == player.get(); }
            )
        );

        return;
    } else player->transfer(tile->getRent(), tile->owner);
}

void Board::move(std::shared_ptr<Player> player) {
    int roll = player->throwDice();
    int newPosition = (player->position + roll) % 28;
    player->position = newPosition;

    Tile* cornerTile = this->tiles[newPosition].get();
    if (cornerTile->getType() == TileType::START) {
        player->deposit(20);
        return;
    }

    if (cornerTile->getType() == TileType::CORNER)
        return;


    SideTile* tile = (SideTile*) this->tiles[newPosition].get();
    std::cout << "Player " << player->id << " has landed on a " << (char) tile->type << " tile!\n";

    if (tile->owner == nullptr && player->balance > tile->getPrice()) {
        if (player->type == PlayerType::BOT) {
            BotPlayer* bot = (BotPlayer*) player.get();
            if (bot->buyTile(tile)) this->buyTerrain(tile, player);
            return;
        }

        std::cout << "Do you want to buy this tile? (S/N): ";
        char answer;
        std::cin >> answer;
        if (answer == 'S' || answer == 's') this->buyTerrain(tile, player);
    } else if (tile->owner != player) {
        std::cout << "Player " << player->id << " has paid " << tile->getRent() << "$ to Player " << tile->owner->id << "!\n";
        this->payRent(tile, player);
    } else {
        if (player->type == PlayerType::BOT) {
            BotPlayer* bot = (BotPlayer*) player.get();
            if (bot->buyTile(tile)) this->buyTerrain(tile, player);
            return;
        }

        std::cout << "Do you want to buy this tile? (S/N): ";
        char answer;
        std::cin >> answer;
        if (answer == 'S' || answer == 's') this->buyTerrain(tile, player);
    }
}