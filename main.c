#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "src/security/crypto.h"
#include "src/security/crypto.c"


void printMenu(){

    printf("\n1. crypt [fic] : Crypter un fichier avec l'aide d'un mot de passe.\n2. dechiffre [fic] : Décrypter un fichier avec l'aide d'un mot de passe.\n3. quit : Quitter.");

}

int main() {
    
    

    printf("Bonjour ! Bienvenue dans votre outil préféré, CryptaBox.\n");

    unsigned char key[32];
    unsigned char iv[AES_BLOCK_SIZE];


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



        if (strcmp(command, "crypt") == 0) {
            printf("\nEntrez le fichier à crypter : ");
            scanf("%s", file);
            
            if (!generateKeyAndIV(key, iv)) {
                printf("\nErreur de génération : clé et/ou vecteur d'initialisation incorrects\n");
                continue;
            }

            if (encryptFile(file, "chiffre.txt", key, iv)) {
                printf("\nFichier chiffré avec succès !\n");
            } else {
                printf("\nÉchec du chiffrement\n");
            }

        } else if (strcmp(command, "dechiffre") == 0) {
            printf("\nEntrez le fichier à déchiffrer : ");
            scanf("%s", file);
            
            if (!generateKeyAndIV(key, iv)) {
                printf("\nErreur de génération : clé et/ou vecteur d'initialisation incorrects\n");
                continue;
            }

            if (dechiffreFile(file, "dechiffre.txt", key, iv)) {
                printf("\nFichier déchiffré avec succès !\n");
            } else {
                printf("\nÉchec du déchiffrement\n");
            }
            
        }else if(strcmp(command,"quit")==0){
            printf("\nbye :)"); 
            
            exit(EXIT_SUCCESS);
        }

           

    

    } while(1);


    exit(EXIT_SUCCESS);
}