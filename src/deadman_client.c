#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#ifndef ERROR
#define ERROR
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
#endif

int callClient()
{
    int sockfd, portno = 9090, n;
    char* hostname = "localhost";
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char* buffer = "alive";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(hostname);
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
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");

    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,sizeof(buffer));
    n = read(sockfd,buffer,sizeof(buffer));
    if (n < 0) 
         error("ERROR reading from socket");
    int deadmanSwitchIsAlive = 0;
    if (strcmp(buffer, "1")) {
    	deadmanSwitchIsAlive = 1;
    }

    printf("%s\n",buffer);
    close(sockfd);
    return deadmanSwitchIsAlive;
}