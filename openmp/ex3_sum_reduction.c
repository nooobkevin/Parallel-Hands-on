#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024L*1024L*128L

// gcc -fopenmp ex3_sum_reduction.c
// time ./a.out

int main() {
    long i, j = 0;
    int * a = malloc(4 * SIZE);
    #pragma omp parallel for
    for (i = 0 ; i < SIZE; i++){
        a[i] = i;
    }

    // Fast and correct
    #pragma omp parallel for reduction(+:j)
    for (i = 0; i < SIZE; i++){
        j += a[i];
    }

    // 9007199187632128
    printf("%ld\n", j);
}