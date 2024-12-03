# wordle-game
 
The NYT game Wordle presents the user with an unknown 5-letter word and gives them 6 guesses to find it. Upon guess, letters within the word are displayed as default color if they are not in the word, yellow if they are in the word but in the wrong place, and in green if they are in the word and in the right spot.

How this will cover the requirements:

Read in a .txt file with 3000+ words
Store words in an array to be chosen from
Pick a random word and split into an array by character (5 individual letters)
Game loop:
Takes in the array of the answer word
Asks for user input, splits into another character array
Compares the two and displays the letters in colors based on rules
Repeat until correct or 6 guesses have been given
Free array memory
Main function will also be a loop that will run through all of this starting with the random word selection, so the user will be able to play again if they wish