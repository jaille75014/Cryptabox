#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cli/commands.h"
#include "security/crypto.h"
#include "network/client.h"
#include "network/server.h"
#include "user_management/auth.h"
#include "user_management/users.h"
#include "user_management/history.h"


int main() {
    int i;
    short int isConnected = 0;

    init_cli();

    do {
        char line[200] = { " " };
        char command[50] = { " " };

        printf("\n=> ");
        if (scanf("%[^\n]", line) != 1) {
            fprintf(stderr, "Erreur de saisie\n");
            while (getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');
        
        for (i = 0; (line[i] != ' ' && line[i] != '\0'); ++i) {
            command[i] = line[i];
        }
        logCommandToDatabase(command);

        if (strcmp(command, "login") == 0) {
            printf("Vous avez choisi de vous connecter\n");
            isConnected = connexionUser();
        } else if (strcmp(command, "register") == 0) {
            printf("Vous avez choisi de vous inscrire\n");
            createAccount();
        } else if (strcmp(command, "quit") == 0) {
            deconnexionUser();
            exit(EXIT_SUCCESS);
        } else if (strcmp(command, "menu") == 0) {
            init_cli();
        } else {
            printf("Erreur : commande inconnue\n");
        }
    } while (isConnected == 0);

    unsigned char key[32];
    unsigned char iv[AES_BLOCK_SIZE];
        
    printMenu();
    do {
        char line[200] = { " " };
        char command[50] = { " " };
        char file[100] = { " " };
        char IP[15] = { "" };

        printf("\nVotre action : \n=> ");

        if (scanf("%[^\n]", line) != 1) {
            fprintf(stderr, "Erreur de saisie\n");
            while (getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        for (i = 0; (line[i] != ' ' && line[i] != '\0'); ++i) {
            command[i] = line[i];
        }
        logCommandToDatabase(command);

        if (strcmp(command, "crypt") == 0) {
            unsigned char key[33];
            unsigned char iv[AES_BLOCK_SIZE];
            memset(key, 0, sizeof(key));
            memset(iv, 0, sizeof(iv));

            printf("\nEntrez le fichier à crypter : ");
            if (scanf("%s", file) != 1) {
                fprintf(stderr, "Erreur de saisie\n");
                continue;
            }
            if (!generateKeyAndIV(key, iv)) {
                printf("\nErreur de génération : clé et/ou vecteur d'initialisation incorrects\n");
                continue;
            }
            if (encryptFile(file, "chiffre.txt", key, iv)) {
                printf("\nFichier chiffré avec succès !\n");
            } else {
                printf("\nÉchec du chiffrement\n");
            }
        } else if (strcmp(command, "decrypt") == 0) {
            printf("\nEntrez le fichier à déchiffrer : ");
            if (scanf("%s", file) != 1) {
                fprintf(stderr, "Erreur de saisie\n");
                continue;
            }

            if (!generateKeyAndIV(key, iv)) {
                printf("\nErreur de génération : clé et/ou vecteur d'initialisation incorrects\n");
                continue;
            }

            if (decryptFile(file, "dechiffre.txt", key, iv)) {
                printf("\nFichier déchiffré avec succès !\n");
            } else {
                printf("\nÉchec du déchiffrement\n");
            }

        } else if (strcmp(command, "send") == 0) {
            
            while (line[i] == ' ') i++;
            if (line[i] == '\0') {
                fprintf(stderr, "\nVeuillez entrer un nom de fichier.");
                continue;
            }

            int j = 0;
            for (; (line[i] != ' ' && line[i] != '\0'); ++i) {
                file[j] = line[i];
                j++;
            }

            while (line[i] == ' ') i++;
            if (line[i] == '\0') {
                fprintf(stderr, "\nVeuillez entrer une IP valide.");
                continue;
            }

            j = 0;
            for (; (line[i] != ' ' && line[i] != '\0'); ++i) {
                IP[j] = line[i];
                j++;
            }

            printf("\nLe fichier que vous souhaitez envoyer est : %s à l'hôte %s : \n", file, IP);
            client(file, IP);

        } else if (strcmp(command, "receive") == 0) {
            receive();

        } else if (strcmp(command, "history") == 0) {
            displayHistory();

        } else if (strcmp(command, "menu") == 0) {
            printMenu();

        } else if (strcmp(command, "quit") == 0) {
            deconnexionUser();
            exit(EXIT_SUCCESS);
        }

    } while (1);

    exit(EXIT_SUCCESS);
}
