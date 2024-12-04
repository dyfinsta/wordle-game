#ifndef GAMELOOP_H
#define GAMELOOP_H

#define MAX_WORDS 3105
#define WORD_LENGTH 5
#define MAX_GUESSES 6

void getWords(char *fileName, char ***words, int *wordCount);
void playGame(char **words, int wordCount, int daily);
void compareWords(char *guess, char *target);

#endif