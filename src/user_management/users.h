/*
    Objectif : Déclarations des fonctions liées aux utilisateurs (création, suppression, authentification et vérification)
    Auteur : Cryptabox
*/

#ifndef USERS_H
#define USERS_H

#include <mysql/mysql.h> 

typedef struct user user;

struct user {
    char username[50];
    char password_hash[64];
};

extern user *currentUser;


MYSQL *connexionDb();
void finish_with_error(MYSQL *con);
int userExist(MYSQL *con, const char *username);
void createAccount();
char *hashPassword(); 

#endif 