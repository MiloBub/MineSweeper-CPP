# MineSweeper-CPP
University second year project. Remake of the Minesweeper game with C++ and SFML.
Planned further development.
To play you must compile the solution because of the problems encountered while pushing to Git.

## Instructions
Main menu:
In main menu you can choose option only by using ARROWS (Up and Down).
By pressing Enter you go to your choosen option.
By pressing Escape (Esc) you close the current window.

Highscore:
The highscore database contain only the 10 best times.
The game was created to be played on a local machine, so highscore would not be erased when the game is closed.
To close the window press Escape (Esc).

Play/In game/Rules of the MineSweeper (state of the 17 of July 2023):
You are challenged with clearing up the board (mine field) containing 8 rows and 8 columns (64 cells) in which are hidden 10 mines.
By pressing Left Mouse Button (LMB) you are discovering the cell and with Right Mouse Button (RMB) you mark the supposed mine.
The cell could be a flag (marked mine), a number from 1-8 or a mine (red square).
The number on a cell shows you how many mines are in 8 surrounding cells.
If you discover a mine you will see a red cell, a LOSE word and the game ends.
If you discover all safe cells (without a mine) the game ends with a WIN word and your time is written to the highscore database (highscore.txt).
To win you MUST discover all safe cells, marking every mine is not required.
You can restart the game by pressing Enter or close the window by pressing Escape (Esc).
