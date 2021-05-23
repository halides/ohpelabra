#include "header/board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void print_board(Board&);
void promote_piece(Piece&);

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[3356];
    bzero(buffer,3356);
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
printf("Connect ok\n");

    while (1) {
        printf("alku\n" );

	bzero(buffer,3356);
        n = read(sockfd, buffer, 3355);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("%s\n", buffer);

	bzero(buffer,3356);
        n = read(sockfd, buffer, 3355);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("%s\n", buffer);

	
        printf("keski\n" );
	bzero(buffer,3356);
        fgets(buffer,3355,stdin);
           n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
        error("ERROR writing to socket");
        printf("loppu\n" );
    }
    close(sockfd);
    return 0;
}