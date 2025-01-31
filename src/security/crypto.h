#if !defined CRYPTO_H
#define CRYPTO_H

#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int generateKeyAndIV(unsigned char *key, unsigned char *iv);
int encryptFile(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv);
int decryptFile(const char *input_file, const char *output_file, unsigned char *key, unsigned char *iv);

#endif