/*
    Objectif : Déclarations des fonctions d'historique
    Auteur : Cryptabox
*/

#ifndef HISTORY_H
#define HISTORY_H


typedef UserHistory * UserHistory;
struct UserHistory {
    char username[50];
    char action[100];
    char timestamp[20];
};

void logUserAction(const char *username, const char *action);
void displayUserHistory(const char *username);

#endif