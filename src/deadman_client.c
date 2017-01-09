#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "deadman_client.h"


#ifndef ERROR
#define ERROR
/*void error(const char *msg)*/
/*{*/
/*    perror(msg);*/
/*    [>exit(0);<]*/
/*}*/
#endif

/*
 * return 0 problem, 1 ok
 */
int callClient(char* hostname, int portno)
{
    if (hostname == NULL) {
            hostname = "localhost";
    }

    if (portno == 0) {
            portno = 9090;
    }


    int deadmanSwitchIsAlive = 0;
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[10];
    char* queryMessage = "alive";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) { 
        error("ERROR opening socket");
        return deadmanSwitchIsAlive;
    }

    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) { 
        error("ERROR connecting");
    } else {

            n = write(sockfd,queryMessage,strlen(queryMessage));
            if (n < 0) { 
                 error("ERROR writing to socket");
            }

            n = read(sockfd,buffer,255);
            if (n < 0) { 
                 error("ERROR reading from socket");
            }

            if (strncmp(buffer, "1", 1) == 0) {
                deadmanSwitchIsAlive = 1;
            }

            printf("%s\n",buffer);
    }

    close(sockfd);
    return deadmanSwitchIsAlive;
}

