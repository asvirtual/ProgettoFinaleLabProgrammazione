#include "Board.h"
#include "CornerTile.h"
#include "TileTerrain.h"

#include <memory>
#include <vector>

int main(void) {
    // std::vector<std::unique_ptr<Tile>> tiles;
    // {
        // std::unique_ptr<Tile> (new CornerTile(0)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 1)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 2)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 3)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 4)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 5)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 6)),
        // std::unique_ptr<Tile> (new CornerTile(7)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 8)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 9)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 10)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 11)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 12)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 13)),
        // std::unique_ptr<Tile> (new CornerTile(14)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 15)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 16)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 17)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 18)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 19)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 20)),
        // std::unique_ptr<Tile> (new CornerTile(21)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 21)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 22)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 23)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 24)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 25)),
        // std::unique_ptr<Tile> (new TileTerrain(TileType::ECONOMY, 26))
    // };

    Tile* t = new CornerTile();

    // tiles.push_back(std::make_unique<CornerTile>(0));
    // tiles.push_back(std::make_unique<TileTerrain>(TileType::ECONOMY, 1));

    // Board b = Board(tiles);
    // b.print();
    return 0;
}