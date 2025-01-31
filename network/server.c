#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> // Pour implémenter des sockets
#include <netinet/in.h> // Pour gérer la structure socket avec la famille de protocole, l'IP et le port d'écoute
#include <netinet/in.h>  // Pour gérer les IPs notamment inet_aton() qui permet https://linux.die.net/man/3/inet_aton

typedef struct sockaddr_in SOCKADDR_IN;

int main(){

    int socketServer = socket(AF_INET,SOCK_STREAM,0); // https://man7.org/linux/man-pages/man2/socket.2.html

    if(socketServer=-1){
        fprintf(stderr,"Erreur à l'initialisation du socket.");
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;
    socketAddress.sin_family=AF_INET;
    socketAddress.sin_port=14972;
    socketAddress.sin_addr.s_addr="127.0.0.1";

    if(bind(socketServer, (struct sockaddr *) &socketAddress,sizeof(socketAddress))==-1){
        fprintf(stderr,"Erreur lors de la liaison entre le socket et ses paramètres.");
        exit(EXIT_FAILURE);
    }

    if(listen(socketServer,1)==-1){
        fprintf(stderr, "Erreur pour écouter des possibles connexions entrantes");
        exit(EXIT_FAILURE);
    }

    printf("En attente de nouvelles connexions.");

    
}