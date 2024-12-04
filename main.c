#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameLoop.h"

int main(){
    char **words = NULL;
    int wordCount;

    //load words
    getWords("word-list.txt", &words, &wordCount);

    while(1){
        printf("\n**WORDLE GAME**\n");
        printf("1. Play with a random word\n");
        printf("2. Play the daily puzzle\n");
        printf("3. Exit game\n");
        printf("Enter selection here: ");

        int choice;
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Playing with random word...\n");
                playGame(words, wordCount, 0);
                break;
            case 2:
                printf("Playing daily puzzle..\n");
                playGame(words, wordCount, 1);
                break;
            case 3:
                printf("Closing game. Thanks for playing!\n");

                //free memory upon game exit
                for(int i=0; i<wordCount; i++){
                    free(words[i]);
                }
                free(words);
                return 0;
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