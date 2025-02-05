#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../global.h"
#include <openssl/sha.h>
#include <mysql/mysql.h>
#include "auth.h"
#include "users.h"

#define MAX_USERNAME 50
#define PASSWORD_MAX_LENGTH 256


int connexionUser() {
    MYSQL *con = connexionDb(); 
    int connected = 0;
     do {
          char username[MAX_USERNAME];


          printf("Entrez votre identifiant :\n=> ");
          if (scanf("%49s", username) != 1) {
               fprintf(stderr, "Identifiant incorrect ou trop long !\n");
               while (getchar() != '\n')
               continue;
               return 0;
          }
               while (getchar() != '\n');


               char *hashedPassword = hashPassword();
               if (!hashedPassword) {
               fprintf(stderr, "Erreur lors du hachage du mot de passe.\n");
               return 0;
               }

               char safeUsername[MAX_USERNAME * 2];
               mysql_real_escape_string(con, safeUsername, username, strlen(username));
               char query[512];
               snprintf(query, sizeof(query),
                    "SELECT COUNT(*) FROM USERS WHERE name='%s' AND password='%s'",
                    safeUsername, hashedPassword);

               if (mysql_query(con, query)) {
                    free(hashedPassword);
                    finish_with_error(con);
               }

          MYSQL_RES *result = mysql_store_result(con);
               if (result == NULL) {
                    free(hashedPassword);
                    finish_with_error(con);
               }

          MYSQL_ROW row = mysql_fetch_row(result);
          int count = 0;
          if (row != NULL) {
               count = atoi(row[0]);
          }

          mysql_free_result(result);

          if (count > 0) {
               printf("Connexion réussie !\n");
               currentUser = malloc(sizeof(struct user));
               if (currentUser == NULL) {
                    fprintf(stderr, "Erreur d'allocation mémoire pour currentUser\n");
                    free(hashedPassword);
                    mysql_close(con);
                    return 0;
               }
               strcpy(currentUser->username, username);
               strcpy(currentUser->password_hash, hashedPassword);
               connected = 1;
          } else {
               fprintf(stderr, "Identifiant ou mot de passe incorrect.\n");
               connected = 0; 
          }
          free(hashedPassword);
     } while (connected == 0);
     mysql_close(con);
     return 1;
}

void deconnexionUser() {
    free(currentUser);
    currentUser = NULL;
    printf("Au revoir !\n");
    exit(EXIT_SUCCESS);
}
