#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "authentication.h"


#define MAX_CLIENTS 5

enum handle {
    EXIT = 0,
    LOGIN = 1, 
    LOGOUT = 2,
};


void *handle_client(void *socket_fd) {
    int client_socket = *((int *)socket_fd);
    char buffer[1024];
    int read_size;

    // Receive data from client
    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        int status = 1;
        switch(status){
            case 0 :
                exit(0);
                break;
            case 1 :
                login(client_socket);
                break;
            case 2 :
                logout(client_socket);
                break;
        }   
    }

    if (read_size == 0) {
        printf("Client disconnected: %d\n", client_socket);
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    // Close the socket and free the thread's socket file descriptor
    close(client_socket);
    free(socket_fd);
    pthread_exit(NULL);
}

int main(int argc,char *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    // Bind the socket
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // Listen for incoming connections
    listen(server_socket, MAX_CLIENTS);

    printf("Server listening on port %d...\n", atoi(argv[1]));

    // Accept incoming connections
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("Accept failed");
            return 1;
        }

        printf("Connection accepted: %d\n", client_socket);

        // Create a new thread to handle the client
        int *new_socket = malloc(1);
        *new_socket = client_socket;

        if (pthread_create(&thread_id, NULL, handle_client, (void *)new_socket) < 0) {
            perror("Could not create thread");
            return 1;
        }

        // Detach the thread to allow it to run independently
        pthread_detach(thread_id);
    }

    close(server_socket);

    return 0;
}

