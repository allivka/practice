#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <arpa/inet.h>

void errore(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    int socketfd, clilen, n;
    char buffer[2056];
    struct sockaddr_in addr_client, addr_server;
    
    if(argc != 3) {
        fprintf(stderr, "ERROR: Usage: test-client <port> <message>");
        exit(EXIT_FAILURE);
    }
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socketfd < 0) {
        errore("Failed creating socket for the server!\n");
    }
    
    bzero((char *) &addr_server, sizeof(addr_server));
    bzero((char *) &addr_client, sizeof(addr_client));
    
    addr_client.sin_family = AF_INET;
    addr_client.sin_port = 0;
    addr_client.sin_addr.s_addr = INADDR_ANY;
    
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(atoi(argv[1]));
    addr_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(bind(socketfd, (struct sockaddr*)&addr_client, sizeof(addr_client)) < 0) {
        errore("ERROR: Failed binding socket");
    }
    
    if(connect(socketfd, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0) {
        errore("ERROR: connecting to server");
    }
    
    n = send(socketfd, argv[2], strlen(argv[2]), 0);
    
    if(n < 0) {
        errore("ERROR: Failed sending data to the server");
    }
    
    printf("Succesfully sent %d bytes of data! : %s\n", n, argv[2]);
    
    n = recv(socketfd, buffer, sizeof(buffer), 0);
    
    if(n < 0) {
        errore("ERROR: Failed receiving data from the server");
        
    }
    
    printf("Succesfully received %d bytes of data! : %s\n", n, buffer);
}