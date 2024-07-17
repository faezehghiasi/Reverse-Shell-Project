//Building and Running:
// 1-Compile the code:
// client.c -o client
// 2-Run the client, specifying the server's IP address and port:
// ./client <port_number> <server_ip>
// For example, to connect to a server at 127.0.0.1 on port 3000
// ./client 3000 127.0.0.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#define MAX_BUFFER 1024
int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <server_ip>\n", argv[0]);
        return 1;
    }
    int port, sockfd,n;
    FILE *fp;
    struct sockaddr_in servaddr;
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
    servaddr.sin_addr.s_addr = inet_addr(argv[2]);
    servaddr.sin_port = htons(port);
    
    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect failed");
        close(sockfd);
        return 1;
    }

    while (1)
    {
        // Clear buffer
        memset(buffer, '\0', strlen(buffer));
        // Receive command from server
        n = recv(sockfd, buffer, MAX_BUFFER, 0);
        if (n <= 0) {
            if (n == 0) {
                printf("Server disconnected.\n");
            } else {
                perror("recv failed");
            }
            return 1;
        }
        // Execute the command using popen
        fp = popen(buffer, "r");
        if (fp == NULL) {
            perror("popen failed");
            break;
        }

        // Clear buffer
        memset(buffer, 0, MAX_BUFFER);

        // Send the output of the command for server
        while (fgets(buffer, MAX_BUFFER, fp)) {
            n = send(sockfd, buffer, strlen(buffer), 0);
            if (n < 0) {
                perror("send failed");
                pclose(fp);  
                break;
            }
        }
        //close the pipe
        pclose(fp);

        // Send end-of-information marker
        memset(buffer, 0, MAX_BUFFER);
        strcpy(buffer, "**");
        n = send(sockfd, buffer, 3, 0);
        if (n < 0) {
            perror("send failed");
            break;
        }
    }

    close(sockfd);
    return 0;
}

