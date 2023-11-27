#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include "authentication.h"
#include "../model/account.h"
#include "../config/config.h"


void login(int client_socket,char *buffer){
    char *argv[5];
    int argc;
    splitString(buffer,argv,&argc);
    if(argc!=4){
        printf("Thieu tham so truyen vao !\n");
        return;
    }
    loginnedAccounts = addAccount(loginnedAccounts,argv[1],argv[2],argv[0]);
    // printf("%s",argv[1]);
}

void logout(int client_socket,char *buffer){
    char *argv[3];
    int argc;
    splitString(buffer,argv,&argc);
    if(argc!=2){
        printf("Thieu tham so truyen vao !\n");
        return;
    }
    removeAccount(&loginnedAccounts,argv[1]);
    printf("Logout %s\n",argv[1]);
}