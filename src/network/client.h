#ifndef CLIENT_H
#define CLIENT_H

int client(char fileName[100], char IP[15]);
FILE * openFile(char fileName[100]);
void sendFile(int socketClient, FILE *file, const char *fileName);

#endif