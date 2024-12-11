#ifndef GAMELOOP_H
#define GAMELOOP_H

#define WORD_LENGTH 5
#define HARD_WORD_LENGTH 7
#define MAX_GUESSES 6

void getWords(char *fileName, char ***words5, char ***words7, int *wordCount5, int *wordCount7);
void playGame(char **words, int wordCount, int daily, int wordLength);
void compareWords(char *guess, char *target);

#endif