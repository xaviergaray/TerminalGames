# TerminalGames
Compilation of various games made during my freetime that run on the Windows terminal.

## CoreMinimum.h
Includes basic functions that are repeated several times across most source files.

## Game Selection
Allows users to select games using terminal GUI.

### UI
TODO:
* Add option for multiple games
* Maintain high score for each game in log files
### Available Games
Currently have Snake

TODO:
* Rocket Defense
* PacMan
* Connect4
* Sudoku

## Snake
Uses std::map to relate each "body part" to a set of coordinates. When character moves, each part replaces its own coordinates with the previous starting from the tail.

TODO:
* Add posion apples
