Enums:
    - TileType (economy, standard, luxury, corner, start)

Classes:
    - Board
    - Tile, parent of:
        - CornerTile
        - SideTile, parent of:
            - TileTerrain
            - TileHouse
            - TileHotel
        
    - Player, parent of:
        - BotPlayer

    Board:
        - vector<Tile> tiles -> Array reprentation of board, every position is a Tile
        - print method
        - Board cell getter method

    Player:
        - int balance
        - vector<Tile> ownedTiles
        - toString override: {player.id}: comma separated owned tiles

    Tile: 
        - TileType tyleType
        - Player owner
        
Helper functions:
    - Log
    