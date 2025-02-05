#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

void init_cli() {
    printf("_______                      _____       ______                \n");
    printf("__  ____/___________  ___________  /______ ___  /___________  __\n");
    printf("_  /    __  ___/_  / / /__  __ \\  __/  __ `/_  __ \\  __ \\_  |/_/\n");
    printf("/ /___  _  /   _  /_/ /__  /_/ / /_ / /_/ /_  /_/ / /_/ /_>  <  \n");
    printf("\\____/  /_/    _\\__, / _  .___/\\__/ \\__,_/ /_.___/\\____//_/|_|  \n");
    printf("               /____/  /_/                                       \n");
    printf("\n");
    printf("\n===============================================\n");
    printf("Hello and welcome in your interactive shell Cryptabox ! Follow US...\n");
    printf("Let's strat by specifying what you want to do: \n");
    printf("\n\tregister : Create your account\n");
    printf("\tlogin: connect with your credentials\n");
    printf("\tmenu : print the menu\n");
    printf("\tquit : logout and quit the Shell\n");
    printf("===============================================\n");
}


void printMenu() {
    printf("_______                      _____       ______                \n");
    printf("__  ____/___________  ___________  /______ ___  /___________  __\n");
    printf("_  /    __  ___/_  / / /__  __ \\  __/  __ `/_  __ \\  __ \\_  |/_/\n");
    printf("/ /___  _  /   _  /_/ /__  /_/ / /_ / /_/ /_  /_/ / /_/ /_>  <  \n");
    printf("\\____/  /_/    _\\__, / _  .___/\\__/ \\__,_/ /_.___/\\____//_/|_|  \n");
    printf("               /____/  /_/                                       \n");

    printf("\n1. crypt : Chiffrer un fichier avec l'aide d'un mot de passe.\n");
    printf("2. decrypt : Déchiffrer un fichier avec l'aide d'un mot de passe.\n");
    printf("3. send [file] [IP] : Envoyer un fichier sur une machine distante.\n");
    printf("4. receive : Accepter de recevoir un fichier.\n");
    printf("4. history : Afficher l'historique de vos commandes.\n");
    printf("4. menu : Afficher le menu.\n");
    printf("5. quit : Quitter.\n");
}