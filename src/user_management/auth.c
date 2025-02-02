#include <stdio.h>
#include <string.h>

#include "global.h"
#include <openssl/sha.h>
#include <mysql.h>
#include "auth.h"
#include "users.h"

#define MAX_USERNAME 50
#define MAX_PASSWORD 30
#define HASH_SIZE 65

int connexionUser() {
    MYSQL *con = connexionDb(); 

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char hashedPassword[HASH_SIZE];

    printf("Entrez votre identifiant :\n=> ");
    scanf("%s", username);

    printf("Entrez votre mot de passe :\n=> ");
    scanf("%s", password);


    hash_password(password, hashedPassword);


    char query[512];
    snprintf(query, sizeof(query),
             "SELECT COUNT(*) FROM USERS WHERE name='%s' AND password='%s'",
             username, hashedPassword);

    if (mysql_query(con, query)) {
         finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
         finish_with_error(con);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = 0;
    if (row != NULL) {
         count = atoi(row[0]);
    }

    mysql_free_result(result);
    mysql_close(con);

    if (count > 0) {
         printf("Connexion réussie !\n");
         currentUser = malloc(sizeof(struct User));
         if (currentUser == NULL) {
             fprintf(stderr, "Erreur d'allocation mémoire pour currentUser\n");
             return 0;
         }
         strcpy(currentUser->username, username);
         strcpy(currentUser->password_hash, hashedPassword);
         return 1;
    } else {
         fprintf(stderr, "Identifiant ou mot de passe incorrect.\n");
         return 0; 
    }
}

void deconnexionUser() {
    free(currentUser);
    currentUser = NULL;
    printf("Au revoir !\n");
}
