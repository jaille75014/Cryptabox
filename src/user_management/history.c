/*
    Objectif : Gestion de l'historique des actions des utilisateurs
    Auteur : Cryptabox
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"


void logCommandToDatabase(const char *command) {
    if (currentUser == NULL) {
        fprintf(stderr, "Aucun utilisateur connecté.\n");
        return;
    }

    MYSQL *con = connexionDb();
    if (con == NULL) {
        fprintf(stderr, "Erreur lors de la connexion à la DB.\n");
        return;
    }
    
    int userId;
    char query[512];
    snprintf(query, sizeof(query),
            "SELECT id FROM USERS WHERE name='%s'",
            currentUser->username);

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        finish_with_error(con);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        fprintf(stderr, "Utilisateur non trouvé\n");
        mysql_free_result(result);
        mysql_close(con);
        return; 
    }

    userId = atoi(row[0]);
    mysql_free_result(result);

    char escapedCommand[1024];
    mysql_real_escape_string(con, escapedCommand, command, strlen(command)); 

    char query[2048];
    snprintf(query, sizeof(query),
             "INSERT INTO HISTORY (user_id, command) VALUES (%d, '%s')",
                userId,
                escapedCommand
             );

    if (mysql_query(con, query)) {
        finish_with_error(con);
    }
    mysql_close(con);
}

/*
CREATE TABLE HISTORY (
    id INTEGER AUTO_INCREMENT PRIMARY KEY,
    user_id INT,           
    command TEXT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES USERS(id)
    );

CREATE TABLE USERS (
    id INTEGER AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(50) NOT NULL,
    password VARCHAR(50) NOT NULL
    );

*/