#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include "auth.h"


int create_account(){
        char id[30];
        char password[25];
        FILE * create_fic =  NULL;
        printf("Entrez votre identifiant :\n=> ");
        scanf("%s", id);

        if((create_fic = fopen(id, "r")) != NULL){
                printf("Un compte existe deja sous ce nom, connectez vous\n");
                return 2;
        }

        if((create_fic = fopen(id, "w")) == NULL){
                printf("Erreur lors de la creation de votre compte, verifiez les droits et votre memoire");
                return 3;
        }
        printf("Choisir un mot de passe sécurisé qui respecte les normes de l'ANSSI :\n=> ");
        scanf("%s", &password);

        printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
        return 2;
}


void hashPassword(const char *password, char *hashedPassword) {
    // En construction
}
