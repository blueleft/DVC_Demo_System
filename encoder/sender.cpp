#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
using namespace std;

#define PORT "3000"
#define BUFSIZE 100

int main(int argv, char** argc) {

    int sockfd, newfd;
    struct addrinfo hints, *servinfo;
    struct sockaddr_storage their_addr;
    
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int rv;
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    
    if((sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0) {
        perror("server: socket");
        return 1;
    }
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
    
    if(bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
        close(sockfd);
        perror("server: bind");
        return 1; 
    }

    if(listen(sockfd, 10) == -1) {
        perror("listen");
        return 1;
    }
    
    socklen_t sin_size = sizeof their_addr;    
    newfd = accept(sockfd, (struct sockaddr*) &their_addr,&sin_size);
    if(newfd < -1) {
        perror("accept");
        return 1;
    }
    
    close(sockfd);    
    
    int fd = open(argc[1], O_RDONLY);
    int n;
    char buf[BUFSIZE];
    while((n = read(fd, buf, sizeof(buf))) > 0) {
        if (send(newfd, buf, n, 0) == -1) 
            perror("send");
    }
    
    close(newfd);

}
