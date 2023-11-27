#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "authentication/authentication.h"
#include "game.h"
#include "model/account.h"

#define MAX_CLIENTS 5

// Lưu danh sách các account có trong database 
extern struct Account *accounts;
extern struct Account *loginnedAccounts;

// enum handle {
//     SIGNUP = 0,
//     LOGIN = 1, 
//     LOGOUT = 2,
//     NEW_ROOM = 3,
//     JOIN = 4,
//     INVITE = 5,
//     LEAVE = 6,
//     CHOOSE = 7,
//     CHAT = 8,
//     READY = 9,
//     START = 10
// };

 
// Hàm tách chuỗi
extern void splitString(char input[], char *result[], int *resultSize) {
    char *token = strtok(input, " "); // Tách chuỗi bằng khoảng trắng
    *resultSize = 0;

    // Lặp để tách và lưu vào mảng result
    while (token != NULL) {
        result[*resultSize] = (char *)malloc(strlen(token) + 1); // Cấp phát bộ nhớ cho mỗi chuỗi
        strcpy(result[*resultSize], token); // Sao chép chuỗi vào mảng result
        (*resultSize)++;
        token = strtok(NULL, " ");
    }
}


// Xử lý request từ client
void *handle_client(void *socket_fd) {
    int client_socket = *((int *)socket_fd);
    char buffer[1024];
    int read_size;

    // Xử lý các luồng cho các loại message 
    while ((read_size = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        // Lấy status code của đoạn tin client gửi tới 
        int i=0;
        while(buffer[i]!=' '){
            i++;
        }
        char *statusCode;
        strncpy(statusCode,buffer,i);
        int status = atoi(statusCode);
        // printf("%d\n",status);

        // Tách luồng để xử lý 
        switch(status){
            case 0 :
                leave();
                break;
            case 1 :
                login(client_socket,buffer);
                break;
            case 2 :
                // logout(client_socket);
                break;
            case 3 :
                newroom();
                break;
            case 4 :  
                join();
                break;
            case 5 :
                invite();
                break;
            case 6 :
                leave();
                break;
            case 7 :
                choose();
                break;
            case 8 :
                chat();
                break;
            case 9 :
                ready();
                break;
            case 10 :
                start();
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
    // login("1","Dong","123");
    // login("2","Phuc","123");
    // login("3","Anh","123");
    // logout(1,"3");
    // displayList(loginnedAccounts);
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

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if(listen(server_socket, MAX_CLIENTS)==-1){
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", atoi(argv[1]));

    // Accept incoming connections
    while (1) {
        // Nhận một kết nối với client mới 
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        
        if (client_socket < 0) {
            perror("Accept failed");
            return 1;
        }
        printf("Connection accepted: %d\n", client_socket);

        // Tạo luồng mới để xử lý cho từng client
        int *new_socket = malloc(1);
        *new_socket = client_socket;

        // Tạo luồng mới
        if (pthread_create(&thread_id, NULL, handle_client, (void *)new_socket) < 0) {
            perror("Could not create thread");
            return 1;
        }
        
        // Tách luồng để xử lý riêng biệt
        pthread_detach(thread_id);
    }

    close(server_socket);

    return 0;
}

