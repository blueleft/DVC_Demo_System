#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
#include <fcntl.h>

using namespace std;

#define PORT "3000"
#define BUFSIZE 100 

int main(int argv, char** argc) {
    int sockfd;
    struct addrinfo hints, *servinfo;
    int rv;
    char buf[BUFSIZE];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
   
    if ((rv = getaddrinfo(argc[1], PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    if ((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype,
                servinfo->ai_protocol)) == -1) {
        perror("client: socket");
        return 1;
    }

    if (connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
            close(sockfd);
        perror("client: connect");
        return 1;
    }

    int fd;
    if((fd = open(argc[2], O_WRONLY, S_IRUSR|S_IWUSR)) < 0) {
        perror("open file");
        return 1;
    }
    int numbytes;
    while ((numbytes = recv(sockfd, buf, BUFSIZE-1, 0)) > 0) {
        write(fd, buf, numbytes);
    }

    close(sockfd);
    close(fd);
}
