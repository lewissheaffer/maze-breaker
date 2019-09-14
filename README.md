# maze-breaker

This is a program to generate and solve mazes. It currently only includes a depth-first search algorithm, but I am currently working on a breadth-first search algorithm to add in a future commit.

AUTHOR
------
Lewis Sheaffer
 
BUILD PREREQUISITES
-------------------

Fairly recent GNU/Linux distribution with gcc compiler with ncurses library 
  (Tested on cygwin32-gcc-core 6.4.0-1 )
  
BUILD INSTRUCTIONS
------------------
If you wish to modify the program, be sure to include a -lncursesw tag when compiling. 

TEST THE PROGRAM
----------------

To test the program you just have to run it in the terminal using the appropriate arguments:

Random Maze: 
  - The second argument tag is the percent wall randomness
  - The third and fourth tags are the number of rows and columns respectively 

``./mazeBreaker Random 30 10 20 ``

File Maze: 
 - To test the program on your own maze, add the maze in the form of a txt file to the mazes directory
 - The maze directory contains a couple mazes to sample from
 - To run, execute as follows with the appropriate file name
 
 ``./mazeBreaker File Mazes\\SampleMaze1.txt``
