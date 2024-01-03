// FTP Client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6500 




int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configure server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //Loopback address I am useing local machine  
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    // Connect to server
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        printf("Connection failed\n");
        return -1;
    }

    // Perform FTP operations (send commands)
    sendCommands(clientSocket);

    close(clientSocket); // Close the client socket

    return 0;
}

