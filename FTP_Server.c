// FTP Server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 6500

int authenticateClient(int clientSocket) {
    char username[50];
    char password[50];
    int authSuccess = 0;

    recv(clientSocket, username, sizeof(username), 0);
    recv(clientSocket, password, sizeof(password), 0);

    // remove the newline character added by fgets
    username[strcspn(username, "\n")] = '\0';
    if (strcmp(username, "p") == 0 && strcmp(password, "p") == 0) {
        printf("Authentication successful\n");
        authSuccess = 1;
    } else {
        printf("Authentication failed\n");
    }
    // Clear the buffer to prepare for the next authentication 
    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    return authSuccess;
}

void handleClient(int socket) {
    // Your implementation of handling FTP commands goes here
    printf("Handling client commands...\n");
}

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        printf("Error creating sockett.\n");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        printf("Error binding socket.\n");
        return -1;
    }


    if (listen(serverSocket, 5) < 0) {
        printf("Error listening for connections.\n");
        return -1;
    }else 
     printf("Listening\n");

    addr_size = sizeof serverStorage;
    // Accept connections from clients    
    newSocket = accept(serverSocket, (struct sockaddr *) &serverStorage, &addr_size);
    if (newSocket < 0) {
        printf("Error accepting connection.\n");
        return -1;
    }

    if (authenticateClient(newSocket)) {
        printf("Authentication successful. State 200\n");
        handleClient(newSocket);
    } else {
        printf("Authentication failed. Connection closed. State 400\n");
    }

    close(newSocket);
    close(serverSocket);

    return 0;
}
