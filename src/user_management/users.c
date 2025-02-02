#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <mysql.h>
#include "auth.h"
#include "users.h"

#define MAX_USERNAME 50
#define MAX_PASSWORD 30
#define HASH_SIZE 65
#define SERVER "192.168.1.36"

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

  if (mysql_real_connect(con, "192.168.1.36", "ajr3mousquetaires", "AJR3MOUSQUETAIRES", "CRYPTABOX", 0, NULL, 0) == NULL) {
        finish_with_error(con);
        }
  return con;
}

char hashPassword() {
    const char* passwordToHash = NULL;
    char* hash = NULL;

    passwordToHash = calloc(SHA256_DIGEST_LENGTH, sizeof(const unsigned char));
    hash = calloc(SHA256_DIGEST_LENGTH, sizeof(char));

    printf("Entrez votre mot de passe :\n");
    fgets((char*) passwordToHash, SHA256_DIGEST_LENGTH, stdin);
    size_t len = strlen((const char*) passwordToHash);
    SHA256(passwordToHash, len, (unsigned char*) hash);

    return 0;
}

int userExist(MYSQL *con, char *username) {
        int nameExist = 0;
        int exist = 0;
    nameExist = mysql_query(conn, "SELECT COUNT(*) FROM USERS WHERE name='%s'", username)
    if (nameExist != 0) {
        return exist = 1;
    } else {
        return exist = 0;
    }
}

void createAccount(){
	int id;
    int isExist;
    char username[MAX_USERNAME];
	char *password;
    
    printf("Entrez votre identifiant :\n=> ");
    scanf("%s", username);

	isExist = userExist(connexionDb(), username);

    if (isExist == 1) {
        printf("Bah alors on pert la boule ? En même temps c'est vrai que ce projet donne mal à la tête...\n");
        mysql_close(con);
        return EXIT_FAILURE;
    }
	    password = hashPassword();

        char query[512];
        snprintf(query, sizeof(query), "INSERT INTO USERS (username, password) VALUES ('%s', '%s')", username, password);

        if (mysql_query(con, query)) {
                finish_with_error(con);
        }

        printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
        mysql_close(con);
}
