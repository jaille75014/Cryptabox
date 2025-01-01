#include <stdio.h>
#include <stdlib.h>
#include "decrypt.h"
#include <openssl/aes.h>
#include <string.h>

// Attention, je crois que la fonction AES_setdecrypt_key est obsolète, faudra utiliser un truc comme EVP_aes_128_ecb() ou un truc du genre
// A voir prcq je suis pas sûr et faut se renseigner sur le concept


int decrypt(const char *encrypted_data, const char *key, char *decrypted_output) {
    AES_KEY aes_key;

    if (AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key) != 0) {
        exit(EXIT_FAILURE);
    }

    // Déchiffrement >> les données doivent être de longueur multiple de 16
    AES_decrypt((const unsigned char *)encrypted_data, (unsigned char *)decrypted_output, &aes_key);

    exit(EXIT_SUCCESS);
}