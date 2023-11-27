#ifndef ACCOUNT_H 
#define ACCOUNT_H

struct Account {
    char username[50];
    char password[50];
    char id[10];
    struct Account *next;
};

struct Account *accounts;

struct Account *addAccount(struct Account *head,const char *username, const char *password, const char *id);

struct Account *getAccountFromFile();

void displayList(struct Account *head);

void saveAccountToDatabase();

void removeAccount(struct Account **head,const char *id);

void signin(char *id,char *username,char *password);

#endif