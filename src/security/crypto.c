#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

int generateKeyAndIV(unsigned char *key, unsigned char *iv) {
    printf("Veuillez entrer la clé de chiffrement (32 caractères) : ");

    if (scanf("%32s", key) != 1) {
        fprintf(stderr, "Erreur de lecture de la clé\n");
        return 0;
    }

    if (strlen((const char *)key) != 32) {
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
    if (!input) {
        fprintf(stderr, "Erreur d'ouverture de %s: %s\n", input_file, strerror(errno));
        return 0;
    }

    FILE *output = fopen(output_file, "wb");
    if (!output) {
        fprintf(stderr, "Erreur d'ouverture de %s: %s\n", output_file, strerror(errno));
        fclose(input);
        return 0;
    }

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

    unsigned char buffer[1024];  // Tampon pour lire les données
    unsigned char textChiffre[1024 + AES_BLOCK_SIZE];  // Tampon pour stocker les données chiffrées
    size_t nbrOctets, textChiffre_len;

    while ((nbrOctets = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        if (EVP_EncryptUpdate(ctx, textChiffre, (int *)&textChiffre_len, buffer, (int)nbrOctets) != 1) {
            fprintf(stderr, "Erreur de chiffrement\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }

        size_t written = fwrite(textChiffre, 1, textChiffre_len, output);
        if (written != textChiffre_len) {
            fprintf(stderr, "Erreur d'écriture dans le fichier de sortie. Nombre d'octets écrits : %ld / %ld\n", written, textChiffre_len);
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
    }

    unsigned char finalText[AES_BLOCK_SIZE];
    if (EVP_EncryptFinal_ex(ctx, finalText, (int *)&textChiffre_len) != 1) {
        fprintf(stderr, "Erreur de finalisation du chiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    size_t written = fwrite(finalText, 1, textChiffre_len, output);
    if (written != textChiffre_len) {
        fprintf(stderr, "Erreur d'écriture finale dans le fichier de sortie. Nombre d'octets écrits: %ld / %ld\n", written, textChiffre_len);
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
    if (!input) {
        fprintf(stderr, "Erreur d'ouverture de %s: %s\n", input_file, strerror(errno));
        return 0;
    }

    FILE *output = fopen(output_file, "wb");
    if (!output) {
        fprintf(stderr, "Erreur d'ouverture de %s: %s\n", output_file, strerror(errno));
        fclose(input);
        return 0;
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
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

    unsigned char buffer[1024]; // Tampon pour lire les données chiffrées
    unsigned char textDechiffre[1024 + EVP_MAX_BLOCK_LENGTH]; // Tampon ajusté pour déchiffrement
    size_t nbrOctets, textDechiffre_len;

    while ((nbrOctets = fread(buffer, 1, sizeof(buffer), input)) > 0) {
        if (EVP_DecryptUpdate(ctx, textDechiffre, (int *)&textDechiffre_len, buffer, (int)nbrOctets) != 1) {
            fprintf(stderr, "Erreur de déchiffrement\n");
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }

        if (fwrite(textDechiffre, 1, textDechiffre_len, output) != textDechiffre_len) {
            fprintf(stderr, "Erreur d'écriture dans le fichier de sortie : %s\n", strerror(errno));
            EVP_CIPHER_CTX_free(ctx);
            fclose(input);
            fclose(output);
            return 0;
        }
    }

    if (EVP_DecryptFinal_ex(ctx, textDechiffre, (int *)&textDechiffre_len) != 1) {
        fprintf(stderr, "Erreur de finalisation du déchiffrement\n");
        EVP_CIPHER_CTX_free(ctx);
        fclose(input);
        fclose(output);
        return 0;
    }

    if (fwrite(textDechiffre, 1, textDechiffre_len, output) != textDechiffre_len) {
        fprintf(stderr, "Erreur d'écriture finale dans le fichier de sortie : %s\n", strerror(errno));
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