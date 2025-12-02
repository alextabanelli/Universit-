#include <inttypes.h>
#include <stdio.h>


/*Scrivere un programma che stampi:
la dimensione in byte dei tipi base (char, int, unsigned int, float, double),
il valore minimo e massimo per interi e floating point (usando <limits.h> e
<float.h>)
*/
#include <limits.h>
#include <float.h>  

int main() {
    printf("Dimensioni in byte:\n");
    printf("char: %zu\n", sizeof(char));
    printf("int: %zu\n", sizeof(int));
    printf("unsigned int: %zu\n", sizeof(unsigned int));
    printf("float: %zu\n", sizeof(float));
    printf("double: %zu\n", sizeof(double));

    printf("\nValori minimi e massimi:\n");
    printf("char: min = %d, max = %d\n", CHAR_MIN, CHAR_MAX);
    printf("int: min = %d, max = %d\n", INT_MIN, INT_MAX);
    printf("unsigned int: min = 0, max = %u\n", UINT_MAX);
    printf("float: min = %e, max = %e\n", FLT_MIN, FLT_MAX);
    printf("double: min = %e, max = %e\n", DBL_MIN, DBL_MAX);

    return 0;
}
