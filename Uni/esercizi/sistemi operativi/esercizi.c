#include<stdio.h>
#include<limits.h>
#include<float.h>

int main(){
    printf("char %zu, min = %d, max = %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("int %zu, min = %d, max = %d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int %zu, min = 0, max = %u\n", sizeof(unsigned int), UINT_MAX);
    printf("float %zu, min = %e, max = %e\n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("double %zu, min = %e, max = %e\n", sizeof(double), DBL_MIN, DBL_MAX);
    return 0;
}

#include <stdio.h>
#include <inttypes.h>

int main(){
    intmax_t a = 500000000000000000;
    printf("%" PRIdMAX "\n", a);
    return 0;
}

#include <stdio.h>

int main() {
    int a = 5;
    int *p = &a;
    printf("Value of a: %d\n", a);
    printf("Address of a: %p\n", &a);
    printf("Value of p (address of a): %p\n", p);
    printf("Value pointed to by p: %d\n", *p);
    return 0;
}




#include <stdio.h>

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 19, b = 42;
    printf("Before swap: a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("After swap: a = %d, b = %d\n", a, b);
    return 0;
}


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

