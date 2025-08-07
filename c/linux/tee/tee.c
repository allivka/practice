#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc != 2 && argc != 3) {
        fprintf(stderr, "Incorrect usage of command");
        exit(EXIT_FAILURE);
    }
    
    char buff;
    
    int flags = O_WRONLY | O_CREAT;
    char *dest;
    
    if(argc == 2) {
        flags |= O_TRUNC;
        dest = argv[1];
    } else if(strcmp(argv[1], "-a") == 0){
        flags |= O_APPEND;
        dest = argv[2];
    } else {
        fprintf(stderr, "Incorrect usage of command");
        exit(EXIT_FAILURE);
    }
    
    int destfd = open(dest, flags, S_IRUSR | S_IWUSR);
    
    while(read(0, &buff, 1) > 0) {
        write(destfd, &buff, 1);
        write(1, &buff, 1);
    }
}