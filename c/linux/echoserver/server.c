#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <unistd.h>

void errore(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int processConnection(int connectionsocketfd) {
    char buffer[2056];
    
    if(connectionsocketfd < 0) {
        return -1;
    }
    
    bzero(buffer, sizeof(buffer));
    int n = recv(connectionsocketfd, buffer, sizeof(buffer), 0);
    
    if(n < 0) {
        perror("ERROR: Failed receiving data from the client");
        return -1;
    }
    
    printf("Succesfully received %d bytes of data! : %s\n", n, buffer);
    
    n = send(connectionsocketfd, buffer, n, 0);
    
    if(n < 0) {
        perror("ERROR: Failed sending data to the client");
        return 1;
    }
    
    printf("Succesfully sent %d bytes of data! : %s\n", n, buffer);
    
    return 0;
}

int main(int argc, char *argv[]) {
    int socketfd, connectionsocketfd, n;
    char buffer[2056];
    struct sockaddr_in addr_server;
    
    if(argc < 0) {
        fprintf(stderr, "ERROR: no port number is provided");
        exit(EXIT_FAILURE);
    }
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socketfd < 0) {
        errore("Failed creating socket for the server!\n");
    }
    
    bzero((char *) &addr_server, sizeof(addr_server));
    
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(atoi(argv[1]));
    addr_server.sin_addr.s_addr = INADDR_ANY;
    
    if(bind(socketfd, (struct sockaddr*)&addr_server, sizeof(addr_server)) < 0) {
        errore("ERROR: Failed binding socket");
    }
    
    if(listen(socketfd, 6) < 0) {
        errore("ERROR: Failed listening");
    }
    
    int clilen = sizeof(addr_server);
    
    while(connectionsocketfd = accept(socketfd, (struct sockaddr*)&addr_server, &clilen)) {
        
        int pid = fork();
        
        if (pid < 0) {
            errore("ERROR: Failed creating new process for client handling");
        }
        
        if (pid > 0) {
            close(connectionsocketfd);
            continue;
        }
        
        processConnection(connectionsocketfd);
        
        exit(EXIT_SUCCESS);
    }
}