#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include "authentication.h"
#include "../model/account.h"
#include "../config/config.h"

// Đăng nhập
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


//Đăng xuất 
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


// Đăng ký 
void signup(int client_socket,char *buffer){
    // Lấy các tham số từ người dùng truyền vào 
    char *argv[3];
    int argc;
    splitString(buffer,argv,&argc);
    if(argc!=3){
        printf("Hoi bi ao :)))) ! \n");
        return;
    }

    numberaccounts++;

    // Lấy id cho người dùng 
    char id[5];
    snprintf(id,sizeof(id),"%d",numberaccounts);

    // Tạo tài khoản mới 
    createAccount(id,argv[1],argv[2]); // Đang lỗi ở chỗ này -> Gọi nó không in được
    printf("Tao tai khoan : %s %s\n",argv[1],argv[2]); 
}