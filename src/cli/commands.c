#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

void init_cli() {
    printf("Bienvenue dans CryptaBox !\n");
    printf("Entrez une commande :\n");
}

void encrypt_file(const char *filename) {
    printf("Chiffrement du fichier : %s\n", filename);
    // Simulation du chiffrement
}

void decrypt_file(const char *filename) {
    printf("Déchiffrement du fichier : %s\n", filename);
    // Simulation du déchiffrement
}