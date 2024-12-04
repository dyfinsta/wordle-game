#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameLoop.h"

void printWords(char **words, int wordCount){
    printf("words:\n");
    for(int i=0; i<wordCount; i++){
        printf("%s\n", words[i]);
    }
    printf("words read: %d\n", wordCount);
}

int main(){
    char **words = NULL;
    int wordCount;

    //load words
    getWords("testWords.txt", &words, &wordCount);

    while(1){
        printf("\n**WORDLE GAME**\n");
        printf("1. Play with a random word\n");
        printf("2. Play the daily puzzle\n");
        printf("3. Exit game\n");
        printf("4. test current work\n");
        printf("Enter selection here: ");

        int choice;
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("playing with random word");
                break;
            case 2:
                printf("playing daily puzzle");
                break;
            case 3:
                printf("Closing game. Thanks for playing!\n");

                //free memory upon game exit
                for(int i=0; i<wordCount; i++){
                    free(words[i]);
                }
                free(words);
                return 0;
            case 4:
                printWords(words, wordCount);
            default:
                printf("Invalid choice, Please enter again.\n");
        }
    }

    for(int i=0; i<wordCount; i++){
        free(words[i]);
    }
    free(words);
    
    return 0;
}