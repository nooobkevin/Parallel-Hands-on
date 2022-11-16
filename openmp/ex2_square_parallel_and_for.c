#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 1024L*1024L*1024L

// gcc -fopenmp ex2_square_parallel_and_for.c
// time ./a.out

int main() {
    long i;
    int * a = malloc(4 * SIZE);
    int * b = malloc(4 * SIZE);

    # pragma omp parallel
    {
        # pragma omp for
        for (i = 0 ; i < SIZE; i++){
            a[i] = i;
        }

        // > 1
        printf("number of threads in between: %d\n", omp_get_num_threads());
        
        # pragma omp for
        for (i = 0; i < SIZE; i++){
            b[SIZE - 1 - i] = a[i]*a[i] - 1;
        }
    }
    // -1 0 3 8
    printf("%d %d %d %d\n", b[SIZE-1], b[SIZE-2], b[SIZE-3], b[SIZE-4]);
}