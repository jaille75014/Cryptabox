/*
    Objectif : Gestion de l'historique des actions des utilisateurs
    Auteur : Cryptabox
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HISTORY 100

typedef struct UserAction UserAction;
struct UserAction {
    char username[50];
    char action[100];
    char timestamp[20];
};

void currentTimestamp(char *timestamp) {
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    sprintf(timestamp, "%d-%02d-%02d %02d:%02d:%02d", // En gros sprintf permet de formater la chaine mais sans l'afficher, on pourra la stocker/afficher plus tard
            tm_info->tm_year + 1900, 
            tm_info->tm_mon + 1,
            tm_info->tm_mday,
            tm_info->tm_hour,
            tm_info->tm_min,
            tm_info->tm_sec);
}

void logUserAction(const char *username, const char *action) {
    FILE *fichier = NULL;
    if ((fichier = fopen("user_actions.txt", "a")) == NULL) {
        fprintf(stderr, "Erreur ouverture du fichier user_actions.txt\n");
        exit(EXIT_FAILURE);
    }

    UserAction userAction;
    strcpy(userAction.username, username);
    strcpy(userAction.action, action);
    currentTimestamp(userAction.timestamp);

    fprintf(fichier, "[%s] %s: %s\n", userAction.timestamp, userAction.username, userAction.action);

    fclose(fichier);
}

void displayUserHistory(const char *username) {
    FILE *fichier = NULL;
    if ((fichier = fopen("user_actions.txt", "r")) == NULL) {
        fprintf(stderr, "Erreur ouverture du fichier user_actions.txt\n");
        exit(EXIT_FAILURE);
    }

    char line[256];
    printf("Historique des actions de %s :\n", username);
    
    while (fgets(line, sizeof(line), fichier)) {
        if (strstr(line, username) != NULL) {
            printf("%s", line);
        }
    }

    fclose(fichier);
}

int main(int argc, char *argv[]) {
    logUserAction("Alban", "Connexion");
    logUserAction("Raf", "Déconnexion");
    logUserAction("Alban", "Changement de mot de passe");

    displayUserHistory("Jules");

    return 0;
}