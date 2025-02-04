#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // Pour implémenter des sockets
#include <netinet/in.h> // Pour gérer la structure socket avec la famille de protocole, l'IP et le port d'écoute
#include <unistd.h>
#include <arpa/inet.h> // Pour la fonction inet_aton() permettant de transformer une adresse IP en binaire
#include "client.h"


typedef struct sockaddr_in SOCKADDR_IN; // sockaddr_in est une structure définie dans <netinet/in.h> permettant de caractérisé notre socket ensuite avec bind()



int client(char fileName[100], char IP[15]){
    FILE *file=NULL;

    if((file = openFile(fileName))==NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    int socketClient;





    if((socketClient= socket(AF_INET,SOCK_STREAM,0))==-1){// https://man7.org/linux/man-pages/man2/socket.2.html
        fprintf(stderr,"Erreur à l'initialisation du socket.\n");
        fclose(file);
        file=NULL;
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;
    socketAddress.sin_family=AF_INET; // TCP    
    socketAddress.sin_port=14972 ; // On écoute sur le port 14972

    if(inet_aton(IP,&socketAddress.sin_addr)!=1){ 
        fprintf(stderr,"Adresse IP invalide.\n");
        fclose(file);
        file=NULL;
        exit(EXIT_FAILURE);
    }



    if(connect(socketClient, (struct sockaddr *) &socketAddress, sizeof(socketAddress))==-1){
        fprintf(stderr, "Impossible de se connecter à la machine cible.\n");
        fclose(file);
        file=NULL;
        exit(EXIT_FAILURE);
    }


    printf("Connexion établie avec %s. Envoi du fichier en cours !\n", IP);
    
    sendFile(socketClient, file, fileName);

    fclose(file);
    file=NULL;

    

    
    close(socketClient);

    exit(EXIT_SUCCESS);
    
}


FILE *openFile(char fileName[100]) {
    FILE *file = NULL;

    if ((file=fopen(fileName, "rb"))==NULL) {
        return file;
    }
    return file;
}


void sendFile(int socketClient, FILE *file, const char *fileName) {

    if (send(socketClient, fileName, 100, 0) == -1) {
        fprintf(stderr,"Erreur lors de l'envoi du nom du fichier\n");
        fclose(file);
        file=NULL;
        close(socketClient);
        exit(EXIT_FAILURE);
    }


    char buffer[1024];
    size_t bytesRead;
    /*while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (send(socketClient, buffer, bytesRead, 0) == -1) {
            fprintf(stderr,"Erreur lors de l'envoi du fichier\n");
            fclose(file);
            file=NULL;
            close(socketClient);
            exit(EXIT_FAILURE);
        }
    }*/

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t totalSent = 0;
        while (totalSent < bytesRead) {
            ssize_t sent = send(socketClient, buffer + totalSent, bytesRead - totalSent, 0);
            if (sent == -1) {
                perror("Erreur lors de l'envoi des données");
                fclose(file);
                close(socketClient);
                exit(EXIT_FAILURE);
            }
            totalSent += sent;
        }
    }

    printf("Fichier envoyé avec succès.\n");
}