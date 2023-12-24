// Author: Giordano Alberti

#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include <random>
#include <string>

#include "Tile.h"
#include "CornerTile.h"
#include "SideTile.h"
#include "Player.h"
#include "BotPlayer.h"
#include "monopoly.h"

/*
    Board class which represents the game board.
    It contains a vector of tiles and a vector of players, and it's responsible for the game logic.
*/
class Board {
    private:
        /*
            Tiles and players are handled with shared pointers as opposed to unique pointers
            as the same pointers are also needed in Player and Tile classes
            to handle the ownership of the tiles and the elimination of the players.
            Pointers are necessary to avoid slicing the objects when they are passed as parameters
        */
        
        std::vector<std::shared_ptr<Tile>> tiles; // Tiles vector (contains all the pointers to the tiles of the board)
        std::vector<std::shared_ptr<Player>> players; // Players vector (contains all the pointers to the players of the game)
        bool humanPlayer; // Boolean that keeps track of the user's choice ("human" or "computer")

        void generateTiles(void); // Generates the tiles of the board
        void generatePlayers(void); // Generates the players of the game
        void buyTerrain(SideTile* tile, const std::shared_ptr<Player>& player); // Buys a terrain, updates the player's money and the tile's owner
        void payRent(SideTile* tile, const std::shared_ptr<Player>& player); // Pays the rent to the owner of the tile, sends a transaction to the owner and updates the player's money
        void buildHouse(SideTile* tile); // Builds a house on the tile, updates the tile's 'building' field and the player's money
        void buildHotel(SideTile* tile);  // Builds a hotel on the tile, updates the tile's 'building' field and the player's money

    public:
        static constexpr int SIDE_LENGTH = 8;
        static constexpr int TILES_COUNT = 28;
        static constexpr int PLAYERS_COUNT = 4;
        static constexpr int MAX_TURNS = 100;

        Board(void); // Default constructor, creates a board with 4 bot players
        Board(bool humanPlayer); // Creates a board with 3 bot players and 1 human player if the user chose "human", otherwise creates a board with 4 bot players
        ~Board() { monopUtil::closeLogFile(); }; // Closes the log file to avoid leaving open resources at the end of the program
        const std::vector<std::shared_ptr<Player>>& getPlayers(void) const { return this->players; };
        void print(void); // Prints the board and the current game stats (tiles owneed by each player and their current balance)
        void move(const std::shared_ptr<Player>& player); // Moves the player and performs various actions based of the tile he landed on
        bool isGameOver(void); // Checks if the game is over (if there is only one player left)
        void getFinalStandings(); // Prints the final standings of the game (the players sorted by their balance)
        int getStartingPosition(void); // Returns the starting position of the board (the "start" tile of the board)
        std::string getUserInput(std::string message); // Gets the player's input during any moment of the turn and returns it as a string

        friend void monopUtil::gameLoop(Board board); // Declares the gameLoop function as a friend of the Board class, so it can access the private field "players" of the Board class
};

#endif