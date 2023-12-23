cmake_minimum_required(VERSION 3.5)
project(ProgettoFinale)

include_directories(include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

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
