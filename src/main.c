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

void printMenu() {
    printf("_______                      _____       ______                \n");
    printf("__  ____/___________  ___________  /______ ___  /___________  __\n");
    printf("_  /    __  ___/_  / / /__  __ \\  __/  __ `/_  __ \\  __ \\_  |/_/\n");
    printf("/ /___  _  /   _  /_/ /__  /_/ / /_ / /_/ /_  /_/ / /_/ /_>  <  \n");
    printf("\\____/  /_/    _\\__, / _  .___/\\__/ \\__,_/ /_.___/\\____//_/|_|  \n");
    printf("               /____/  /_/                                       \n");

    printf("\n1. crypt : Chiffrer un fichier avec l'aide d'un mot de passe.\n");
    printf("2. decrypt : Déchiffrer un fichier avec l'aide d'un mot de passe.\n");
    printf("3. send [fic] [IP] : Envoyer un fichier sur une machine distante.\n");
    printf("4. receive : Accepter de recevoir un fichier.\n");
    printf("5. quit : Quitter.\n");
}

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

    do {
        char line[200] = { " " };
        char command[50] = { " " };
        char file[100] = { " " };
        char IP[15] = { "" };

        printMenu();
        printf("\nVotre action : ");

        if (scanf("%[^\n]", line) != 1) {
            fprintf(stderr, "Erreur de saisie\n");
            while (getchar() != '\n');
            continue;
        }

        for (i = 0; (line[i] != ' ' && line[i] != '\0'); ++i) {
            command[i] = line[i];
        }
        logCommandToDatabase(command);

        if (strcmp(command, "crypt") == 0) {
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

            if (decryptFile(file, "dechiffSre.txt", key, iv)) {
                printf("\nFichier déchiffré avec succès !\n");
            } else {
                printf("\nÉchec du déchiffrement\n");
            }

        } else if (strcmp(command, "send") == 0) {
            i = 0;
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

            printf("\nLe fichier que vous souhaitez envoyer est : %s à l'hôte %s : ", file, IP);
            client(file, IP);

        } else if (strcmp(command, "receive") == 0) {
            receive();

        } else if (strcmp(command, "quit") == 0) {
            deconnexionUser();
            exit(EXIT_SUCCESS);
        }

    } while (1);

    exit(EXIT_SUCCESS);
}