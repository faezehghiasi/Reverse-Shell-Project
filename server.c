//Building and Running:
// 1-Compile the code:
// server.c -o server
// 2-Run the server, specifying the desired port number:
// ./server <port_number>
// For example, to run the server on port 3000:
// ./server 3000 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include<sys/time.h>
#pragma warning (disable:4996)
#define MAX_BUFFER 1024
int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }    
    int port, sockfd, clientfd,n;
    struct sockaddr_in servaddr, clientaddr;
    char buffer[MAX_BUFFER];
    
    // Parse port number 
    port = atoi(argv[1]);

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        return 1;
    }
    // Set up server address
    memset(&servaddr, 0, sizeof(servaddr));  // Initialize to zero for safety
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);


      // Bind the socket to the address
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        if (errno == EADDRINUSE) {
            printf("Error: Port %d is already in use.\n", port);
        } else {
            perror("bind failed");
        }
        close(sockfd);  
        return 1;
    }
    // Listen for incoming connections
    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        close(sockfd);
        return 1;
    }
    // Accept a client connection
    socklen_t clientaddr_len = sizeof(clientaddr);
    clientfd = accept(sockfd, (struct sockaddr *)&clientaddr, &clientaddr_len);
    if (clientfd < 0) {
        perror("accept failed");
        close(sockfd);
        return 1;
    }
    printf("A new client connected to the server : %s\n", inet_ntoa(clientaddr.sin_addr));

    while (1)
    {        
       
       // Clear the buffer
        memset(buffer, 0, MAX_BUFFER);

        // Display server prompt with client IP
        printf("\n%s $", inet_ntoa(clientaddr.sin_addr));

        n = scanf("%[^\n]%*c", buffer);
        if (n <= 0) {
            perror("scanf failed");
            break;  
        }
        // Send the command to the client
        n = send(clientfd, buffer, strlen(buffer), 0);
        if (n < 0) {
            perror("send failed");
            break;

        }

        // Clear the buffer 
        memset(buffer, 0, MAX_BUFFER);

        // Wait for client response with timeout
        struct timeval tiv;
        tiv.tv_sec = 0;
        tiv.tv_usec = 500000;  // 0.5 second timeout
        setsockopt(clientfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tiv, sizeof(tiv));

        // Receive data from the client
        while ((n = recv(clientfd, buffer, MAX_BUFFER, 0)) > 0)
        {   
            if(buffer[n-2] == '*' && buffer[n-3] == '*'){
                buffer[n-3]='\0';
                printf("%s", buffer);
                break;
            }
            printf("%s", buffer);
            memset(buffer, '\0', strlen(buffer));
        }
    }
    close(sockfd);
    close(clientfd);
    return 0;
}
