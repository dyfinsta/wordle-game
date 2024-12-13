# wordle-game
 
The NYT game Wordle presents the user with an unknown 5-letter word and gives them 6 guesses to find it. Upon guess, letters within the word are displayed as default color if they are not in the word, yellow if they are in the word but in the wrong place, and in green if they are in the word and in the right spot. This program is a spin on this with some harder puzzles, of longer word length.

Main features (and how they cover the requirements):
- Reads in words from files, and dynamically allocates and expands arrays to store them.
- Trims words as they are read in, as to not cause conflicts with the gameloop.
- Frees memory without leaks before the program is closed.
- Functioning UI loop and game loop
- User has option to play with random words or the daily word (chosen using functionality of time.h)

How to run (makefile commands):
- "make" or "make all" will compile all files
- "make clean" will remove all .o files
- "make run" will build the project (if not done previously), and run the program