#ifndef GAMELOOP_H
#define GAMELOOP_H

#define WORD_LENGTH 5
#define HARD_WORD_LENGTH 7
#define MAX_GUESSES 6
#define MAX_LENGTH 9

void getWords(char *fileName, char ***words5, char ***words7, int *wordCount5, int *wordCount7);
void playGame(char **words, int wordCount, int daily, int wordLength);
void compareWords(char *guess, char *target, int wordLength);
void getWordsArbitrary(char *fileName, char ***words, int *wordCount);
void trimTrailing(char *str);
void playGameArb(char **words, int wordCount, int daily);

#endif