#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// #include "src/security/encrypt.h"
// #include "src/security/decrypt.h"
void printMenu(){

    printf("\n1. crypt [fic] : Crypter un fichier avec l'aide d'un mot de passe.\n2. decrypt [fic] : Décrypter un fichier avec l'aide d'un mot de passe.\n3. quit : Quitter.");

}

int main() {
    
    

    printf("Bonjour ! Bienvenue dans votre outil préféré, CryptaBox.\n");

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