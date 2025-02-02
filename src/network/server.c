#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // Pour implémenter des sockets
#include <netinet/in.h> // Pour gérer la structure socket avec la famille de protocole, l'IP et le port d'écoute
#include <unistd.h>
#include "server.h"

typedef struct sockaddr_in SOCKADDR_IN; // sockaddr_in est une structure définie dans <netinet/in.h> permettant de caractérisé notre socket ensuite avec bind()

int server(){

    char maxClient=1;

    int socketServer = socket(AF_INET,SOCK_STREAM,0); // https://man7.org/linux/man-pages/man2/socket.2.html

    if(socketServer==-1){
        fprintf(stderr,"Erreur à l'initialisation du socket.\n");
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;

    socketAddress.sin_family=AF_INET; // TCP    
    socketAddress.sin_port=14972 ; // On écoute sur le port 14972
    socketAddress.sin_addr.s_addr=INADDR_ANY; // On accepte les connexions depuis n'importe quelle IP de notre serveur

    if(bind(socketServer, (struct sockaddr *) &socketAddress,sizeof(socketAddress))==-1){
        fprintf(stderr,"Erreur lors de la liaison entre le socket et ses paramètres.\n");
        exit(EXIT_FAILURE);
    }

    

    if(listen(socketServer,maxClient)==-1){ // Listen permet de mettre en écoute le serveur
        fprintf(stderr, "Impossible d'écouter les connexions entrantes\n");
        exit(EXIT_FAILURE);
    }

    printf("En attente de nouvelles connexions.\n");

    socklen_t addrlen = sizeof(socketAddress);
    int socketClient = accept(socketServer, (struct sockaddr*)&socketAddress, &addrlen);


    if(socketClient==-1){
        fprintf(stderr,"Erreur à la connexion entre le client et le serveur.\n");
        exit(EXIT_FAILURE);
    }

    printf("Transfert du fichier en cours.\n");


    char buffer[1024]={0};
    int receivedBytes= recv(socketClient,buffer,1024,0);
    
    if (receivedBytes==-1){
        fprintf(stderr,"Erreur lors de réception du fichier.\n");
        exit(EXIT_FAILURE);

    }

    printf("Client : %s", buffer);

    close(socketServer);
    close(socketClient);

    exit(EXIT_SUCCESS);
    
}