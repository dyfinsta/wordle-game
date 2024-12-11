#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameLoop.h"

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
        line[strcspn(line, "\n")] = '\0'; //remove newline
        
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