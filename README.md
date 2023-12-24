# ProgettoFinaleLabProgrammazione
Giordano Alberti, Andrea Boscarin, Federico Zardo
Progetto finale per il corso di Laboratorio di Programmazione

Project structure:
The project is made of three main classes (Board, Player and Tile) from which other sub-classes are derived.
The Tile class and its children are mainly data classes, as they're used to keep track of the type, buildings
and resulting price/rent of every tile.
Player and its child BotPlayer classes are also mainly data classes and they're used to handle payments
and to keep track of all the tiles owned by each player. The BotPlayer class simply adds a function to
randomly simulate the process of decision-making to handle the scenarios where the bot has to decide whether 
to buy/build a terrain/house/hotel or not.
The Board class is responsible for the turns logic and for printing the board to the terminal in a human-readable
format, as it handles the actions to perform after the players' movements, the elimination of players, the user input
when the "human" mode is chosen and the initialization of the tiles and players objects.