#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gameLoop.h"

int main(){
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
                printf("playing with random word");
                break;
            case 2:
                printf("playing daily puzzle");
                break;
            case 3:
                printf("Closing game. Thanks for playing!\n");
                return 0;
            default:
                printf("Invalid choice, Please enter again.\n");
        }
    }
    return 0;
}