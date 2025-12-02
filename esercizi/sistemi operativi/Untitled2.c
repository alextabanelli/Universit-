#include <stdio.h>
#include <stdlib.h>


int *genera_array(int n) {
    int *array = calloc(n, sizeof(int)); //sizeof(int) vuol dire che sono celle di interi
    /*for (int i = 0; i < n; i++) {
        array[i] = i + 1;
    }*/
    return array;
}

void print_array(int *array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    int size = 0;
    printf("Enter array size:\n ");
    scanf("%d", &size);
    int *array = NULL;
    array = genera_array(size);
    printf("Generated array: ");
    print_array(array, size);
    free(array);
    return 0;
}
