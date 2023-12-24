#ifndef TILETYPE_H
#define TILETYPE_H

/*
    TileType enum class which represents the type of a tile.
    It's used to determine which actions to perform when
    a player lands on a specific tile.
*/
enum class TileType {
    CORNER = ' ',
    START = 'P',
    ECONOMY = 'E',
    STANDARD = 'S',
    LUXURY = 'L'
};

#endif