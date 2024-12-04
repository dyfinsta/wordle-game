#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gameLoop.h"

void getWords(char *fileName, char ***words, int *wordCount){
    FILE *file = fopen(fileName, "r");
    if (!file){
        printf("Error opening word file\n");
        return 0;
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
        if(strlen(line) == 0){
            break;
        }

        if(*wordCount >= capacity) {
            capacity *= 2;
            *words = realloc(*words, capacity * sizeof(char *));
            if(!*words){
                printf("Memory allocation for word failed");
                fclose(file);
                return;
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
        }
    }

    fclose(file);
}