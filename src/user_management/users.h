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


int createUser(const char *username, const char *password);
int authenticateUser(const char *username, const char *password);
int deleteUser(const char *username);
int checkUserExist(const char *username);

#endif