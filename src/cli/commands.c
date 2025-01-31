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
    printf("Bonjour ! Bienvenue dans votre shell interactif Cryptabox ! Je vais vous guider...\n");
    printf("Commencez par indiquer ce que vous souhaitez faire : \n");
    printf("\ninscription : créer votre compte\n");
    printf("\tconnexion: vous connecter\n");
    printf("\tmenu : reafficher le menu\n");
    printf("\tquit : Quitter le shell\n");
    printf("===============================================\n");
}



void encrypt_file(const char *filename) {
    printf("Chiffrement du fichier : %s\n", filename);
    // Simulation du chiffrement
}

void decrypt_file(const char *filename) {
    printf("Déchiffrement du fichier : %s\n", filename);
    // Simulation du déchiffrement
}
