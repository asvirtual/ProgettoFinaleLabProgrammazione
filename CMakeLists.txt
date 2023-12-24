cmake_minimum_required(VERSION 3.5)
project(ProgettoFinale)

include_directories(include)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(main 
	src/main.cpp
	src/Board.cpp
	src/BotPlayer.cpp
	src/CornerTile.cpp
	src/Player.cpp
	src/SideTile.cpp
	src/monopoly.cpp
	src/Tile.cpp
)
