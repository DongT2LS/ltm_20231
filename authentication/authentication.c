#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include "authentication.h"
#include "../model/account.h"

void login(int client_socket,char *buffer){
    char *argv[3];
    int *argc;
    
    loginnedAccounts = addAccount(loginnedAccounts,username,password,id);

}

void logout(int client_socket,char *id){
    removeAccount(&loginnedAccounts,id);
}