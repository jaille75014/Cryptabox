#include <stdio.h>
#include <string.h>
//      #include <openssl/sha.h>
#include <mysql.h>
#include "auth.h"
#include "users.h"

#define MAX_USERNAME = 50
#define MAX_PASSWORD = 30
#define HASH_SIZE = 65

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}


int connexionDb()
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL) {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "$0tchi$Mysql", "CRYPTABOX", 0, NULL, 0) == NULL) {
        finish_with_error(con);
        }

  if (mysql_query(con, "USE DATABASE CRYPTABOX")) {
      finish_with_error(con);
  }
  return con;
}

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)password, strlen(password), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[HASH_SIZE - 1] = '\0';
}

int userExist(MYSQL *con, char *username) {
        int nameExist = 0;
        int exist = 0;
    nameExist = mysql_query(conn, "SELECT COUNT(*) FROM users WHERE name='%s'", username)
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
	char fichier = "files/user_creation.txt";
        char password[MAX_PASSWORD];
	char hashPassword[HASH_SIZE];
        FILE * addInFile =  NULL;
        printf("Entrez votre identifiant :\n=> ");
        scanf("%s", username);

	isExist = userExist(connexionDb(), username);

    if (isExist == 1) {
        printf("Bah alors on pert la boule ? En même temps c'est vrai que ce projet donne mal à la tête...\n");
        mysql_close(con);
        return EXIT_FAILURE;
    }

        printf("Choisir un mot de passe sécurisé qui respecte les normes de l'ANSSI :\n=> ");
        scanf("%s", password);
	hashPassword(password, hashedPassword);

        char query[512];
        snprintf(query, sizeof(query), "INSERT INTO USERS (username, password) VALUES ('%s', '%s')", username, hashedPassword);

        if (mysql_query(con, query)) {
                finish_with_error(con);
        }

        printf("Votre compte a ete créé avec succès, vous pouvez vous connecter\n");
        mysql_close(con);
}
