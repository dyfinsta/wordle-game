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

    printf("Selected word is: %s\n", target);
}