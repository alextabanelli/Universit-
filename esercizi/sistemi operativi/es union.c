#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

union Number {
    int32_t i;
    float f;
    unsigned char bytes[4];
};

void printUnionBytes(const unsigned char *b, size_t n) {
    for (size_t k = 0; k < n; k++) {
        printf("%02x", b[k]);
    }
    printf("\n");
}

int main() {
    union Number n;
    n.i = 0x01020304;
    printf("i = 0x%08x -> bytes: ", (unsigned)n.i);
    printUnionBytes(n.bytes, sizeof(n.bytes));

    n.f = 1.0f;
    printf("f = %.6f -> bytes: ", n.f);
    printUnionBytes(n.bytes, sizeof(n.bytes));
    printf("i = %d\n", n.i);
    return 0;
}
