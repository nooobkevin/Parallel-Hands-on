#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024L*1024L*128L

// gcc -fopenmp ex3_sum_atomic.c
// time ./a.out

int main() {
    long i, j = 0;
    int * a = malloc(4 * SIZE);
    #pragma omp parallel for
    for (i = 0 ; i < SIZE; i++){
        a[i] = i;
    }

    // Not faster than serial, atomic effectively make it serial
    #pragma omp parallel for
    for (i = 0; i < SIZE; i++){
        #pragma omp atomic
        j += a[i];
    }
    
    // 9007199187632128
    printf("%ld\n", j);
}