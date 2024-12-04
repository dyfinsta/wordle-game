#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameLoop.h"

void getWords(char *fileName, char ***words, int *wordCount){
    FILE *file = fopen(filename, "r");
    if (!file){
        printf("Error opening word file\n");
        exit();
    }
    
    *wordCount = 0;
    size_t capacity = 10; //start with small capacity
    *words = malloc(capacity * sizeof(char *));
    if(!*words){
        printf("Memory allocation failed");
        exit();
    }

    char line[WORD_LENGTH + 2]; //extra space for newline
    while (fgets(line, sizeof(line), file)){
        line[strcspn(line, "\n")] = '\0'; //remove newline
        if(strlen(line) == 0){
            break;
        }

        if(*wordCount >= capacity) {
            capacity *= 2;
            *words = realloc(*words, capacity * sizeof(char *));
            if(!*words){
                printf("Memory allocation for word failed");
                exit();
            }
            strncpy((*words)[*wordCount], line, WORD_LENGTH);
            (*words)[*wordCount][WORD_LENGTH] = '\0';
            (*wordCount)++;
        }

        fclose(file);
    }
    
}