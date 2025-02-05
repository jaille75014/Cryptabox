#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include "client.h"


typedef struct sockaddr_in SOCKADDR_IN; 



int client(char fileName[100], char IP[15]){
    FILE *file=NULL;

    if((file = openFile(fileName))==NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    int socketClient;





    if((socketClient= socket(AF_INET,SOCK_STREAM,0))==-1){
        fprintf(stderr,"Erreur à l'initialisation du socket.\n");
        fclose(file);
        file=NULL;
        exit(EXIT_FAILURE);
    }

    SOCKADDR_IN socketAddress;
    socketAddress.sin_family=AF_INET; 
    socketAddress.sin_port=14972 ; 

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
    char*newFileName=strrchr(fileName,'/');
    
    if (send(socketClient, newFileName!=NULL?newFileName+1:fileName, 100, 0) == -1) {
        fprintf(stderr,"Erreur lors de l'envoie du nom du fichier\n");
        fclose(file);
        file=NULL;
        close(socketClient);
        exit(EXIT_FAILURE);
    }


    char buffer[1024];
    size_t bytesRead;
    

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        size_t total = 0;
        while (total < bytesRead) {
            ssize_t sent = send(socketClient, buffer + total, bytesRead - total, 0);
            if (sent==-1) { 
                fprintf(stderr, "Erreur lors de l'envoie du fichier..\n");
                fclose(file);
                close(socketClient);
                exit(EXIT_FAILURE);
            }
            total += sent;  
        }
    }

    printf("Fichier envoyé avec succès.\n");
    
}
