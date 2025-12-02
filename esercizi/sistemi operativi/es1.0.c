#include <stdio.h>

#pragma pack(1)

typedef struct Data1 {
    char a;
    int b;
    short c;
} Data1;

typedef struct Data2 {
    char a;
    short c;
    int b;
} Data2;

#pragma pack(0)

int main () {
    printf("Size of Data1: %zu bytes\n", sizeof(Data1));
    printf("Size of Data2: %zu bytes\n", sizeof(Data2));
    return 0;
}