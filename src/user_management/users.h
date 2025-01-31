/*
    Objectif : Déclarations des fonctions liées aux utilisateurs (création, suppression, authentification et vérification)
    Auteur : Cryptabox
*/

#ifndef USERS_H
#define USERS_H

typedef struct User * User;
struct User {
    char username[50];
    char password_hash[64];
};


int connexionDb();
int hashPassword(const char *password, char *hashed_password);
int userExist(MYSQL *con, char *username);
int createAccount();
void finish_with_error(MYSQL *con);

#endif