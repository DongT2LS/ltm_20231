#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include "authentication.h"


void login(int client_socket){
    // send(client_socket,"Login success !",16,0);
    printf("Login");
}

void logout(int client_socket){
    // send(client_socket,"Logout !",9,0);
    printf("Logout");
}