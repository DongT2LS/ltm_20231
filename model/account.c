#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "account.h"

#define FILENAME "database/account.txt"

// Lấy số lượng tài khoản có trong database
int numberaccounts = 0;

// Thêm mới tài khoản vào danh sách account
struct Account *addAccount(struct Account *head, const char *username, const char *password, const char *id)
{
    // Tạo một vùng nhớ mới để lưu account mới
    struct Account *newAccount = (struct Account *)malloc(sizeof(struct Account));
    if (newAccount == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Cấu hình cho account mới 
    strcpy(newAccount->username, username);
    strcpy(newAccount->password, password);
    strcpy(newAccount->id, id);

    if (head == NULL)
    {
        // Nếu head rỗng thì head sẽ là newAccount
        head = newAccount;
    }
    else
    {
        // Đẩy vị trí của newAccount lên đầu dslk
        newAccount->next = head;
        head = newAccount;
    }

    return head;
}

void removeAccount(struct Account **head,const char *id){
    struct Account *current = *head; // tài khoản đang được kiểm tra
    struct Account *prev = NULL; // Tài khoản tiếp theo 

    // Nếu current có id chưa thỏa mãn thì đặt prev = current và current trỏ vào account tiếp theo 
    while (current != NULL && strcmp(current->id, id) != 0) {
        prev = current;
        current = current->next;
    }
    

    // Nếu chưa kết thúc danh sách liên kết và tìm được account có id trùng thì bắt đầu xóa nút 
    if (current != NULL) {
        if (prev == NULL) {
            // Nếu tài khoản cần xóa là đầu danh sách
            *head = current->next;
        } else {
            // Nếu tài khoản cần xóa không phải là đầu danh sách thì gán lại next của prev là account tiếp theo của current sau đỏ giải phóng bộ nhớ current
            prev->next = current->next;
        }

        free(current);
    } else {
        // Nếu không tìm thấy in ra thông báo 
        printf("Account not found: %s\n", id);
    }
    
}

// Test xem code dung chua 
void displayList(struct Account *head)
{
    while (head != NULL)
    {
        printf("%s %s\n", head->username, head->password);
        head = head->next;
    }
}


// Lấy tất cả tài khoản và mật khẩu có trong file lưu vào dslk
struct Account *getAccountFromFile() 
{
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("Khong the mo tep %s\n", FILENAME);
        return NULL;
    }
    // Khởi tạo con trỏ đầu và cuối
    struct Account *head = NULL;
    struct Account *tail = NULL;

    char username[50], password[50], id[10];

    while (fscanf(file, "%s %s %s", id, username, password) == 3) // Nếu đọc đủ 3 trường của 1 account thì tiếp tục đọc
    {
        // Đếm số lượng tài khoản 
        numberaccounts++;
        // Khởi tạo 1 account mới
        struct Account *newAccount = (struct Account *)malloc(sizeof(struct Account));
        strcpy(newAccount->username, username);
        strcpy(newAccount->password, password);
        strcpy(newAccount->id,id);
        newAccount->next = NULL;

        // Thực hiện đưa account mới đọc được vào dslk
        if (head == NULL)
        {
            head = newAccount;
            tail = newAccount;
        }
        else
        {
            tail->next = newAccount;
            tail = newAccount;
        }
    }

    fclose(file);
    return head; // Trả về con trỏ đầu tiên của dslk
}

// Lưu tất cả tài khoản vào trong database 
void saveAccountToDatabase()
{
    FILE *file = fopen(FILENAME, "w");
    if (file != NULL)
    {
        // tài khoản hiện tại đang được đọc đến 
        struct Account *current = accounts;

        while (current != NULL)
        {
            fprintf(file, "%s %s %s\n", current->id, current->username, current->password); // Thực hiện ghi lại file
            current = current->next; // Chuyển đến account tiếp theo
        }
        fclose(file); // Đóng kết nối với file khi đã ghi xong
    }
    else
    {
        printf("Can't open file\n");
    }
}

// Đăng ký tài khoản mới và lưu vào database và danh sách liên kết 
void createAccount(char *id,char *username,char *password){
    accounts = addAccount(accounts,username,password,id);
    FILE *file = fopen(FILENAME,"a");
    fprintf(file,"%s %s %s\n",id,username,password);
    fclose(file);
}

// void findAccount

