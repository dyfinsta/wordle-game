#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameLoop.h"

int main(){
    char **words5 = NULL;
    char **words7 = NULL;
    int wordCount5;
    int wordCount7;

    //load words
    getWords("word-list.txt", &words5, &words7, &wordCount5, &wordCount7);

    while(1){
        printf("\n\e[1;92m**WORDLE GAME**\n");
        printf("\e[1;93m1. Play with a random word\n");
        printf("2. Play the daily puzzle\n");
        printf("3. Play Hard Mode\n");
        printf("4. Play the hard daily puzzle\n");
        printf("\e[1;91m5. Exit game\n\e[0;37m");
        printf("Enter selection here: ");

        int choice;
        scanf("%d", &choice);

        switch(choice){
            case 1:
                printf("Playing with random word...\n");
                playGame(words5, wordCount5, 0, WORD_LENGTH);
                break;
            case 2:
                printf("Playing daily puzzle..\n");
                playGame(words5, wordCount5, 1, WORD_LENGTH);
                break;
            case 3:
                printf("Playing on hard mode...\n");
                playGame(words7, wordCount7, 0, HARD_WORD_LENGTH);
                break;
            case 4:
                printf("Playing hard daily puzzle...\n");
                playGame(words7, wordCount7, 1, HARD_WORD_LENGTH);
                break;
            case 5:
                printf("Closing game. Thanks for playing!\n");
                
                //free memory upon game exit
                for(int i=0; i<wordCount5; i++){
                    free(words5[i]);
                }
                free(words5);
                //free memory upon game exit
                for(int i=0; i<wordCount7; i++){
                    free(words7[i]);
                }
                free(words7);
                return 0;
            default:
                printf("Invalid choice, Please enter again.\n");
        }
    }
    
    return 0;
}