#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

void init_cli() {
    printf("\n===============================================\n");
    printf("Bonjour ! Bienvenue dans votre shell interactif Cryptabox ! Je vais vous guider...\n");
    printf("Commencez par indiquer ce que vous souhaitez faire : \n");
    printf("\t1 : créer votre compte\n");
    printf("\t2 : vous connecter\n");
    printf("\t3 : reafficher le menu\n");
    printf("\t4 : Quitter le shell\n");
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
