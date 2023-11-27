#ifndef AUTHENTICATION_H 
#define AUTHENTICATION_H

struct Account *loginnedAccounts;
void login(int client_socket,char *buffer);
void logout(int client_socket,char *buffer);

#endif