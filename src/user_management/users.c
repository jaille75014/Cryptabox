#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql/mysql.h>
#include "auth.h"
#include "users.h"
#include "../../global.h"


#define MAX_USERNAME 50
#define PASSWORD_MAX_LENGTH 256
#define HASH_SIZE 65
#define SERVER "localhost"
#define USERNAME "AJR3MOUSQUETAIRES"
#define PASSWORD "MonSuperMotDePasse"

user *currentUser = NULL;

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}


MYSQL *connexionDb() { 
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, SERVER, USERNAME, PASSWORD, "CRYPTABOX", 0, NULL, 0) == NULL) {
        finish_with_error(con);
        }
  return con;
}



char *hashPassword() {
    char password[PASSWORD_MAX_LENGTH];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char *passwordHash = calloc(SHA256_DIGEST_LENGTH * 2 + 1, sizeof(char));

    if (!passwordHash) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        free(passwordHash);
        return NULL;
    }

    printf("Entrez votre mot de passe :\n");
    if (scanf("%255s", password) != 1) {
        fprintf(stderr, "Erreur de lecture du mot de passe.\n");
        free(passwordHash);
        return NULL;
    }
    

    
    
    SHA256((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(passwordHash + (i * 2), "%02x", hash[i]);
    }

    return passwordHash; 
}

int userExist(MYSQL *con, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM USERS WHERE username='%s'", username);
    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    int exist = atoi(row[0]);
    mysql_free_result(result);

    return exist;
}

void createAccount(){
    MYSQL *con = connexionDb();
    int isExist;
    char username[MAX_USERNAME];
    char *password;

    printf("Entrez votre identifiant (max %d caractères) :\n=> ", MAX_USERNAME - 1);
    if (scanf("%49s", username) != 1) {
        fprintf(stderr, "Identifiant incorrect ou trop long !\n");
        return;
    }
    fflush(stdin);

    isExist = userExist(con, username);

    if (isExist > 0) {
        printf("Bah alors on pert la boule ? En même temps c'est vrai que ce projet donne mal à la tête...\n");
        mysql_close(con);
        exit(EXIT_FAILURE);
    }

    password = hashPassword();

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO USERS (username, password) VALUES ('%s', '%s')", username, password);

    if (mysql_query(con, query)) {
        free(password);
        finish_with_error(con);
    } else {
        printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
        free(password);
        mysql_close(con);
    }
}
