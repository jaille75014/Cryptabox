#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
// #include "src/security/encrypt.h"
// #include "src/security/decrypt.h"
void printMenu(){

    printf("\n1. Crypter un fichier avec l'aide d'un mot de passe.\n2. Décrypter un fichier avec l'aide d'un mot de passe.\n3. Quitter.");

}

int main() {
    char action=0;

    printf("Bonjour ! Bienvenue dans votre outil préféré, CryptaBox.\n");

    do {

        do{
            
            printMenu();

            printf("\nVotre action : ");
            scanf("%d",&action);

            if(action<1||action>3){
                fprintf(stderr,"Entrez une option valide.");
            }

        } while(action<1||action>3);

    

    } while(1);


    exit(EXIT_SUCCESS);
}