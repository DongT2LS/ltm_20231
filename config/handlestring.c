#include "config.h"
#include <string.h>
#include <stdlib.h>
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