#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main(int argc,char *argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char message[1024];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    printf("Connected to server\n");

    // Send and receive messages
    // while (1) {
        // printf("Enter message: ");
        // fgets(message, sizeof(message), stdin);

        // Send the message to the server
        send(client_socket, "0 dong212 dong123", 18, 0);

        // Receive the server's response
        // if (recv(client_socket, message, sizeof(message), 0) == 0) {
        //     printf("Server disconnected\n");
        //     break;
        // }

        // printf("Server response : OKE\n");
        // memset(message, 0, sizeof(message));
        // usleep(200000);
    // }

    close(client_socket);

    return 0;
}
