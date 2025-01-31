#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// #include "src/security/encrypt.h"
// #include "src/security/decrypt.h"
#include "src/cli/commands.c"

void printMenu(){

    printf("\n1. crypt [fic] : Crypter un fichier avec l'aide d'un mot de passe.\n2. decrypt [fic] : Décrypter un fichier avec l'aide d'un mot de passe.\n3. quit : Quitter.");

}

int main() {
	
    short int choice = 3;

    while (1) {
        switch (choice) {
            case 1:
                choice = create_account();
                break;
            case 2:
                printf("Vous avez choisi de vous connecter.\n");
                break;
            case 3:
                init_cli();
                choice = 0;
                break;
            case 4:
                printf("Au revoir !\n");
                exit(EXIT_SUCCESS);
            default:
                printf("=> ");
                scanf("%hd", &choice);
                fflush(stdin);
                printf("\n");
        }
    }

    do {

        char line[200]={" "};
        char command[50]={" "};



        fflush(stdin);

    
            
        printMenu();

        printf("\nVotre action : ");
        scanf("%[^\n]",line);

        for(int i=0; (line[i]!=' ' && line[i]!='\0');++i){
            command[i]=line[i];
        }

        if(strcmp(command,"crypt")==0){

            printf("\ncrypt :)"); 
            
            
        } else if(strcmp(command,"decrypt")==0){
            printf("\ndecrypt :)"); 
            
        }else if(strcmp(command,"quit")==0){
            printf("\nbye :)"); 
            
            exit(EXIT_SUCCESS);
        }

           

    

    } while(1);


    exit(EXIT_SUCCESS);
}
