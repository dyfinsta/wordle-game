#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameLoop.h"

void getWords(char *fileName, char ***words, int *wordCount){
    FILE *file = fopen(fileName, "r");
    if (!file){
        printf("Error opening word file\n");
        return;
    }
    
    *wordCount = 0;
    size_t capacity = 10; //start with small capacity
    *words = malloc(capacity * sizeof(char *));
    if(!*words){
        printf("Memory allocation failed");
        fclose(file);
        return;
    }

    char line[WORD_LENGTH + 2]; //extra space for newline
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0'; //remove newline
        
        if(strlen(line) == 0){ //skip empty lines
            continue;
        }

        //allocate memory
        (*words)[*wordCount] = malloc((WORD_LENGTH +1) * sizeof(char));
        if(!(*words)[*wordCount]){
            printf("Memory allocation for words failed");
            fclose(file);
            return;
        }

        strncpy((*words)[*wordCount], line, WORD_LENGTH);
        (*words)[*wordCount][WORD_LENGTH] = '\0';
        (*wordCount)++;

        if(*wordCount >= capacity) {
            capacity *= 2;
            *words = realloc(*words, capacity * sizeof(char *));
            if(!*words){
                printf("Memory allocation for word failed");
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
}

void compareWords(char *guess, char *target){
    for(int i=0; i<WORD_LENGTH; i++){
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

void playGame(char **words, int wordCount, int daily){
    char target[WORD_LENGTH + 1];

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

    printf("Target word chosen. Game start!\n");

    for (int attempt = 1; attempt<= MAX_GUESSES; attempt++){
        char guess[WORD_LENGTH + 1];
        printf("Guess %d/%d: ", attempt, MAX_GUESSES);
        scanf("%5s", guess);

        if(strlen(guess) != WORD_LENGTH) {
            printf("Invalid input. Please enter a 5-letter word.\n");
            attempt--;
            continue;
        }

        compareWords(guess, target);

        if(strcmp(guess, target) == 0) {
            printf("Congratulations! You guessed the word!\n");
            return;
        }
    }
    printf("You ran out of guesses. The word was: %s\n", target);
}