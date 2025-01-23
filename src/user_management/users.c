/*
    Objectif : Gestion des utilisateurs (création, suppression, authentification et vérification)
    Auteur : Cryptabox
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "users.h"
#include "auth.h"


#define MAX_USERS 100
static User users[MAX_USERS];
static int userCount = 0;



int checkUserExist(const char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}


int createUser(const char *username, const char *password) {

    if (checkUserExist(username)) {
        printf("L'utilisateur existe déjà ! Ah ba oui faut pas perdre la boule hein, même si le projet donne mal au crâne...\n");
        exit(EXIT_FAILURE);
    }

    char passwordHash[64];
    hashPassword(password, passwordHash);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].passwordHash, passwordHash);
    userCount++;

    return 0;
}

int authenticateUser(const char *username, const char *password) {

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            char passwordHash[64];
            hashPassword(password, passwordHash);
            if (strcmp(users[i].passwordHash, passwordHash) == 0) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
    
}

int deleteUser(const char *username) {

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = i; j < userCount - 1; j++) {
                users[j] = users[j + 1];
            }
            userCount--;
            return 0;
        }
    }
    return -1;
}