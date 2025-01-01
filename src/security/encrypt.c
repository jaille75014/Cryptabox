#include <stdio.h>
#include <stdlib.h>
#include "encrypt.h"
#include <openssl/aes.h>
#include <string.h>

// Attention, je crois que la fonction AES_set_encrypt est obsolète, faudra utiliser un truc comme EVP_aes_128_ecb() ou un truc du genre
// A voir prcq je suis pas sûr et faut se renseigner sur le concept

int encrypt(const char *data, const char *key, char *encrypted_output) {
    AES_KEY aes_key;

    if (AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key) != 0) {
        exit(EXIT_FAILURE);
    }

    // Chiffrement >> les données doivent être de longueur multiple de 16
    AES_encrypt((const unsigned char *)data, (unsigned char *)encrypted_output, &aes_key);


    exit(EXIT_SUCCESS);
}