#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "gameLoop.h"


//get words is the first function for reading in, this was made to only read in the file with 5 words
//it was later updated to also read in 7 letter words from the file and store them in a separate list
void getWords(char *fileName, char ***words5, char ***words7, int *wordCount5, int *wordCount7){
    FILE *file = fopen(fileName, "r");
    if (!file){
        printf("Error opening word file\n");
        return;
    }
    
    *wordCount5 = 0;
    *wordCount7 = 0;

    size_t capacity5 = 10; //start with small capacity
    size_t capacity7 = 10; 
    *words5 = malloc(capacity5 * sizeof(char *));
    *words7 = malloc(capacity7 * sizeof(char *));
    if(!*words5 || !*words7){
        printf("Memory allocation failed");
        fclose(file);
        return;
    }

    char line[HARD_WORD_LENGTH + 2]; //extra space for newline
    while (fgets(line, sizeof(line), file)){
        char *ptr = line + strlen(line) - 1;
        while(ptr >= line && (*ptr == '\n' || *ptr =='\r')){
            *ptr = '\0';
            ptr--;
        }
        
        if(strlen(line) == 0){ //skip empty lines
            continue;
        }

        if(strlen(line) == WORD_LENGTH) { //store 5 leter words
            if(*wordCount5 >= capacity5) {
                capacity5 *=2;
                *words5 = realloc(*words5, capacity5 * sizeof(char *));
                if(!*words5){
                    printf("Memory reallocation of 5 letter words failed\n");
                    fclose(file);
                    return;
                }
            }
            (*words5)[*wordCount5] = malloc((WORD_LENGTH + 1) * sizeof(char));
            if(!(*words5)[*wordCount5]){
                printf("Memory allocation failed for a 5 letter word\n");
                fclose(file);
                return;
            }
            strcpy((*words5)[*wordCount5], line);
            (*wordCount5)++;
        }else if(strlen(line) == HARD_WORD_LENGTH) { //store 7 letter words
            if(*wordCount7 >= capacity7){
                capacity7 *= 2;
                *words7 = realloc(*words7, capacity7 * sizeof(char *));
                if(!*words7){
                    printf("Memory reallocation of 7 letter words failed\n");
                    fclose(file);
                    return;
                }
            }
            (*words7)[*wordCount7] = malloc((HARD_WORD_LENGTH + 1) * sizeof(char));
            if(!(*words7)[*wordCount7]){
                printf("Memory allocation failed for a 7 letter word\n");
                fclose(file);
                return;
            }
            strcpy((*words7)[*wordCount7], line);
            (*wordCount7)++;
        }
    }

    fclose(file);
}

//compareWords is the logic that gets called by the gameplay functions
//per the name, it compares the user word to the target word to create the main puzzle solving aspect of the game
void compareWords(char *guess, char *target, int wordLength){
    for(int i=0; i<wordLength; i++){
        if(guess[i] == target[i]){
            printf("{\033[32m%c\033[0m}", guess[i]); //correct letter in correct spot
        }else if(strchr(target, guess[i])){
            printf("{\033[33m%c\033[0m}", guess[i]); //correct letter in wrong place
        }else{
            printf("{\033[37m%c\033[0m}", guess[i]); //incorrect letter
        }
    }
    printf("\n");
}

//playGame is the gameloop that selects a target word and allows for the user to input their guesses
//works with the lists of word that have set length
void playGame(char **words, int wordCount, int daily, int wordLength){
    char target[wordLength + 1];

    if(daily){
        //get current date
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        //get day of the year
        int currentDay = tm_info->tm_yday;

        strcpy(target, words[currentDay % wordCount]);
    }else{
        srand(time(NULL));
        strcpy(target, words[rand() % wordCount]);
    }

    printf("\e[1;95mTarget word chosen. Game start!\n\e[0;37m");

    for (int attempt = 1; attempt<= MAX_GUESSES; attempt++){
        char guess[wordLength + 1];
        printf("Guess %d/%d: ", attempt, MAX_GUESSES);
        scanf("%s", guess);

        if(strlen(guess) != wordLength) {
            printf("Invalid input. Please enter a %d-letter word.\n", wordLength);
            attempt--;
            continue;
        }

        compareWords(guess, target, wordLength);

        if(strcmp(guess, target) == 0) {
            printf("Congratulations! You guessed the word!\n");
            return;
        }
    }
    printf("You ran out of guesses. The word was: %s\n", target);
}


//trims trailing spaces from words, this is only used for reading in the words of arbitrary length
void trimTrailing(char *str){
    int end = strlen(str) - 1;
    while (end >= 0 && isspace((char)str[end])){
        str[end] = '\0';
        end--;
    }
}

//reads in the file of the words with varying length.
//separate from the other file reader due to the differences in logic
void getWordsArbitrary(char *fileName, char ***words, int *wordCount){
    FILE *file = fopen(fileName, "r");
    if (!file){
        printf("Error opening word file\n");
        return;
    }
    
    *wordCount = 0;

    size_t capacity = 10;
    *words = malloc(capacity * sizeof(char *));
    if(!words){
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    char line[MAX_LENGTH + 2]; //extra space for newline
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0'; //remove newline
        trimTrailing(line);
        
        if(strlen(line) == 0){ //skip empty lines
            continue;
        }

        if(*wordCount >= capacity) {
                capacity *=2;
                char **temp = realloc(*words, capacity * sizeof(char *));
                if(!temp){
                    printf("Memory reallocation failed\n");
                    for(int i=0; i < *wordCount; i++){
                        free((*words)[i]);
                    }
                    free(*words);
                    fclose(file);
                    return;
                }
                *words = temp;
            }
            (*words)[*wordCount] = malloc((strlen(line) + 1) * sizeof(char));
            if(!(*words)[*wordCount]){
                printf("Memory allocation failed for word\n");
                for(int i=0; i < *wordCount; i++){
                    free((*words)[i]);
                }
                free(*words);
                fclose(file);
                return;
            }
            strcpy((*words)[*wordCount], line);
            (*wordCount)++;
    }
    fclose(file);
}

//gameloop for words of arbitrary length. Rather than words being set length, it determines length within the function
void playGameArb(char **words, int wordCount, int daily){
    char *target;

    if(daily){
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        int currentDay = tm_info->tm_yday;

        target = words[currentDay % wordCount];
    }else{
        srand(time(NULL));
        target = words[rand() % wordCount];
    }

    size_t wordLength = strlen(target);

    printf("\e[1;95mTarget word chosen. Game start!\n\e[0;37m");

    for (int attempt = 1; attempt<= MAX_GUESSES; attempt++){
        char guess[wordLength + 1];
        printf("Guess %d/%d: ", attempt, MAX_GUESSES);
        scanf("%s", guess);

        if(strlen(guess) != wordLength) {
            printf("Invalid input. Please enter a %d-letter word.\n", wordLength);
            attempt--;
            continue;
        }

        compareWords(guess, target, wordLength);

        if(strcmp(guess, target) == 0) {
            printf("Congratulations! You guessed the word!\n");
            return;
        }
    }
    printf("You ran out of guesses. The word was: %s\n", target);
}