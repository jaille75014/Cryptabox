#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "auth.h"

#define MAX_USERNAME = 50
#define MAX_PASSWORD = 30
#define HASH_SIZE = 65


void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASH_SIZE - 1] = '\0';
}


int createAccount(){
	int id;
        char username[MAX_USERNAME];
	char fichier = "files/user_creation.txt";
        char password[MAX_PASSWORD];
	char hashPassword[HASH_SIZE];
        FILE * addInFile =  NULL;
        printf("Entrez votre identifiant :\n=> ");
        scanf("%s", username);

	if(userExist(username)){
		fprintf(stderr, "un user existe déjà avec ce nom, connectez vous si c'est votre compte");
		exit(EXIT_FAILURE);
	}

        if((create_fic = fopen(id, "r")) != NULL){
                printf("Un compte existe deja sous ce nom, connectez vous\n");
                return 2;
        }

        printf("Choisir un mot de passe sécurisé qui respecte les normes de l'ANSSI :\n=> ");
        scanf("%s", password);
	hashPassword(password, hashedPassword);

	if((addInFile = fopen(fichier, "a")) == NULL){
		fprintf(stderr, "Impossible d'ajouter un utilisateur dans ce fichier");
		return 3;
	}
	fprintf(addInFile, "%d %s %s\n", id, username, hashePassword);
	fclose(addInFile);
        printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
        return 2;
}


void hashPassword(const char *password, char *hashedPassword) {
    // En construction
}
