#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.h"
#include "../user_management/history.c"


int generateKeyAndIV(unsigned char *key, unsigned char *iv) {

    printf("Veuillez entrer la clé de chiffrement : ");
    
    char command[256];
    snprintf(command, sizeof(command), "Entrée de la clé de chiffrement : %s", key);
    logCommandToDatabase(command);

    if (scanf("%32s", key) != 1) {
        fprintf(stderr, "Erreur de lecture de la clé\n");
        return 0;
    }

    if (strlen((const char*)key) != 32) {
        fprintf(stderr, "La clé doit faire 32 caractères !\n");
        return 0;
    }

    if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1) {
        fprintf(stderr, "Erreur de génération du Vecteur d'Initialisation\n");
        return 0;
    }

    return 1;
}

int encryptFile(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv) {

    FILE *input = fopen(input_file, "rb");
    if (input == NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s\n", input_file);
        return 0;
    }

    FILE *output = fopen(output_file, "wb");
    if (output == NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s\n", output_file);
        fclose(input);
        return 0;
    }


    // Contexte de chiffrement : structure d'openSSL pour gérer le chiffrement
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        fprintf(stderr, "Erreur de création du contexte de chiffrement\n");
        fclose(input);
        fclose(output);
        return 0;
    }

    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        fprintf(stderr, "Erreur d'initialisation du chiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }


    unsigned char buffer[1024]; // Tampon : lire les données en entrée
    unsigned char textChiffre[1024 + AES_BLOCK_SIZE]; // Tampon : stocker les données chiffrées et padding
    int nbrOctets, textChiffre_len;


    while ((nbrOctets = fread(buffer, 1, 1024, input)) > 0) {
        if (EVP_EncryptUpdate(ctx, textChiffre, &textChiffre_len, buffer, nbrOctets) != 1) {
            fprintf(stderr, "Erreur de chiffrement\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
        if (fwrite(textChiffre, 1, textChiffre_len, output) != textChiffre_len) {
            fprintf(stderr, "Erreur d'écriture dans le fichier de sortie\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
    }

    if (EVP_EncryptFinal_ex(ctx, textChiffre, &textChiffre_len) != 1) {
        fprintf(stderr, "Erreur de finalisation du chiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    if (fwrite(textChiffre, 1, textChiffre_len, output) != textChiffre_len) {
        fprintf(stderr, "Erreur d'écriture finale dans le fichier de sortie\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    EVP_CIPHER_CTX_free(ctx);
    fclose(input);
    fclose(output);
    return 1;
}



int decryptFile(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv) {

    FILE *input = fopen(input_file, "rb");
    if (input == NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s\n", input_file);
        return 0;
    }

    FILE *output = fopen(output_file, "wb");
    if (output == NULL) {
        fprintf(stderr, "Erreur d'ouverture de %s\n", output_file);
        fclose(input);
        return 0;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        fprintf(stderr, "Erreur de création du contexte de déchiffrement\n");
        fclose(input);
        fclose(output);
        return 0;
    }

    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        fprintf(stderr, "Erreur d'initialisation du déchiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }


    unsigned char buffer[1024]; // Tampon : lire les données chiffrées
    unsigned char textDechiffre[1024 + EVP_MAX_BLOCK_LENGTH]; // Tampon : stocker les données déchiffrées et padding
    int nbrOctets, text_len;

    while ((nbrOctets = fread(buffer, 1, 1024, input)) > 0) {
        if (EVP_DecryptUpdate(ctx, textDechiffre, &text_len, buffer, nbrOctets) != 1) {
            fprintf(stderr, "Erreur de déchiffrement\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
        if (fwrite(textDechiffre, 1, text_len, output) != text_len) {
            fprintf(stderr, "Erreur d'écriture dans le fichier de sortie\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
    }

    if (EVP_DecryptFinal_ex(ctx, textDechiffre, &text_len) != 1) {
        fprintf(stderr, "Erreur de finalisation du déchiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    if (fwrite(textDechiffre, 1, text_len, output) != text_len) {
        fprintf(stderr, "Erreur d'écriture finale dans le fichier de sortie\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    EVP_CIPHER_CTX_free(ctx);
    fclose(input);
    fclose(output);
    return 1;
}