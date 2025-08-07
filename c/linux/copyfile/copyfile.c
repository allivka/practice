#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Incorrect usage of command");
        exit(EXIT_FAILURE);
    }
    
    int fdSource = open(argv[1], O_RDONLY);

    if(fdSource == -1) {
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    int fdDestination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if(fdDestination == -1) {
        perror(argv[2]);
        exit(EXIT_FAILURE);
    }

    char buff;

    while(read(fdSource, &buff, 1) > 0) {
        if(buff == 0) {
            lseek(fdDestination, 1, SEEK_CUR);
        } else {
            write(fdDestination, &buff, 1);
        }
    }
    
    if(close(fdSource) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if(close(fdDestination) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}
