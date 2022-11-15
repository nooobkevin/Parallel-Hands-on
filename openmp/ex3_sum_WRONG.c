#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024L*1024L*128L

// gcc -fopenmp ex3_sum_WRONG.c
// time ./a.out

int main() {
    long i, j = 0;
    int * a = malloc(4 * SIZE);
    #pragma omp parallel for
    for (i = 0 ; i < SIZE; i++){
        a[i] = i;
    }

    // Fast but WRONG
    #pragma omp parallel for
    for (i = 0; i < SIZE; i++){
        j += a[i];
    }

    // Correct: 9007199187632128
    printf("%ld\n", j);
}