#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cli/commands.c"
#include "src/security/crypto.h"
#include "src/security/crypto.c"

void printMenu(){

    printf("_______                      _____       ______                \n");
    printf("__  ____/___________  ___________  /______ ___  /___________  __\n");
    printf("_  /    __  ___/_  / / /__  __ \\  __/  __ `/_  __ \\  __ \\_  |/_/\n");
    printf("/ /___  _  /   _  /_/ /__  /_/ / /_ / /_/ /_  /_/ / /_/ /_>  <  \n");
    printf("\\____/  /_/    _\\__, / _  .___/\\__/ \\__,_/ /_.___/\\____//_/|_|  \n");
    printf("               /____/  /_/                                       \n");


    printf("\n1. crypt [fic] : Crypter un fichier avec l'aide d'un mot de passe.\n2. dechiffre [fic] : Décrypter un fichier avec l'aide d'un mot de passe.\n3. quit : Quitter.");

}

int main() {

    short int choice = 3;
    do {    
        init_cli();
        char line[200]={" "};
        char command[50]={" "};

        printf("\nVotre action : ");
        scanf("%[^\n]",line);
        for(int i=0; (line[i]!=' ' && line[i]!='\0');++i){
                command[i]=line[i];
            }

        if(strcmp(command, "connexion") == 0){
                printf("Vous avez choisi de vous connecter.\n");
                return EXIT_SUCCESS;
        } else if (strcmp(command, "inscription") == 0) {
                printf("Vous avez choisi de vous inscrire.\n");
                return EXIT_SUCCESS;
        } else if (strcmp(command, "quitter") == 0) {
                printf("Au revoir !\n");
                return EXIT_SUCCESS;
        } else if (strcmp(command, "menu") == 0) {
            choice = init_cli();
        } else {
            printf("Erreur : commande inconnue.\n");
        }
    } while (choice == 3);

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



        if (strcmp(command, "chiffre") == 0) {
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
