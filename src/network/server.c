#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include "server.h"

typedef struct sockaddr_in SOCKADDR_IN; 

int receive(){
    ssize_t receivedBytes;
    int socketServer, socketClient;
    char buffer[1024];
    char fileName[100] = {0};


    char maxClient=1;


    if((socketServer= socket(AF_INET,SOCK_STREAM,0))==-1){
        fprintf(stderr,"Erreur à l'initialisation du socket.\n");
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;

    socketAddress.sin_family=AF_INET; 
    socketAddress.sin_port=14972 ; 
    socketAddress.sin_addr.s_addr=INADDR_ANY; 

    if(bind(socketServer, (struct sockaddr *) &socketAddress,sizeof(socketAddress))==-1){
        fprintf(stderr,"Erreur lors de la liaison entre le socket et ses paramètres.\n");
        close(socketServer);
        exit(EXIT_FAILURE);
    }

    

    if(listen(socketServer,maxClient)==-1){ 
        fprintf(stderr, "Impossible d'écouter les connexions entrantes\n");
        close(socketServer);
        exit(EXIT_FAILURE);
    }

    printf("En attente de nouvelles connexions...\n");

    socklen_t addrlen = sizeof(socketAddress);


    if((socketClient= accept(socketServer, (struct sockaddr*)&socketAddress, &addrlen))==-1){
        fprintf(stderr,"Erreur à la connexion entre le client et le serveur.\n");
        close(socketServer);
        exit(EXIT_FAILURE);
    }

    printf("Client connecté ! Le fichier est en cours de réception...\n");


    if (recv(socketClient, fileName, 100, 0) ==-1){
        fprintf(stderr,"Erreur lors de réception du nom du fichier.\n");
        close(socketClient);
        close(socketServer);
        exit(EXIT_FAILURE);
    }

    FILE *file = NULL;
    if((file=fopen(fileName,"wb"))==NULL){
        fprintf(stderr,"Erreur lors de la création du fichier");
        close(socketClient);
        close(socketServer);
        exit(EXIT_FAILURE);
    }

    while ((receivedBytes = recv(socketClient, buffer, 1024, 0)) > 0) {
        fwrite(buffer, 1, receivedBytes, file);
    }

    if (receivedBytes == -1) {
        fprintf(stderr,"Erreur lors de la réception du fichier");
    } else {
        printf("Fichier reçu avec succès.\n");
    }



    fclose(file);
    close(socketServer);
    close(socketClient);

    exit(EXIT_SUCCESS);
    
}
