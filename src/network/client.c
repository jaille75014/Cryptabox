#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // Pour implémenter des sockets
#include <netinet/in.h> // Pour gérer la structure socket avec la famille de protocole, l'IP et le port d'écoute
#include <unistd.h>
#include <arpa/inet.h> // Pour la fonction inet_aton() permettant de transformer une adresse IP en binaire
#include "client.h"


typedef struct sockaddr_in SOCKADDR_IN; // sockaddr_in est une structure définie dans <netinet/in.h> permettant de caractérisé notre socket ensuite avec bind()

int client(){

    

    int socketClient = socket(AF_INET,SOCK_STREAM,0); // https://man7.org/linux/man-pages/man2/socket.2.html

    if(socketClient==-1){
        fprintf(stderr,"Erreur à l'initialisation du socket.\n");
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;

    socketAddress.sin_family=AF_INET; // TCP    
    socketAddress.sin_port=14972 ; // On écoute sur le port 14972

    if(inet_aton("127.0.0.1",&socketAddress.sin_addr)!=1){ // Voir si on met inet_pton() pour supporter l'IPv6
        fprintf(stderr,"Adresse IP invalide.\n");
        exit(EXIT_FAILURE);
    }



    if(connect(socketClient, (struct sockaddr *) &socketAddress, sizeof(socketAddress))==-1){
        fprintf(stderr, "Impossible de se connecter à la machine cible.\n");
        exit(EXIT_FAILURE);
    }





    


    
    if (send(socketClient,"TESTT",strlen("TESTT"),0)==-1){
        fprintf(stderr,"Erreur lors de réceptil'envoie du fichier.\n");
        exit(EXIT_FAILURE);
    }

    

    
    close(socketClient);

    exit(EXIT_SUCCESS);
    
}