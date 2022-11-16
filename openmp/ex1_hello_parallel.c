#include <stdio.h>

// gcc -fopenmp ex1_hello_parallel.c
// ./a.out
// OMP_NUM_THREADS=4 ./a.out

int main() {
    # pragma omp parallel
    printf("HellOMP world\n");
}
