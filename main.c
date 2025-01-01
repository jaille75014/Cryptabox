#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "src/security/encrypt.h"
#include "src/security/decrypt.h"


int main() {
    const char *data = "exemplededata123"; // 16 octets
    const char *key = "0123456789abcdef"; // 16 octets (clé fixe)
    char encrypted_data[16];
    char decrypted_data[16];


    if (encrypt(data, key, encrypted_data) == 0) {
        printf("Données chiffrées : ");
        for (int i = 0; i < 16; i++) {
            printf("%02x", (unsigned char)encrypted_data[i]);
        }
        printf("\n");
    } else {
        printf("Erreur lors du chiffrement !\n");
    }

    if (decrypt(encrypted_data, key, decrypted_data) == 0) {
        printf("Données déchiffrées : %s\n", decrypted_data);
    } else {
        printf("Erreur lors du déchiffrement !\n");
    }


    exit(EXIT_SUCCESS);
}