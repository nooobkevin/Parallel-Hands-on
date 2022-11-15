#include <stdio.h>
#include <unistd.h>

#define MAX 5

// gcc -fopenmp ex4_sleep_nowait_barrier.c
// ./a.out

int main() {
    int i;

    #pragma omp parallel
    {
        #pragma omp for nowait
        for (i = 0 ; i < MAX; i++){
            sleep(i);
            printf("a: %d\n", i);
        }

        #pragma omp barrier

        #pragma omp for
        for (i = 0 ; i < MAX; i++){
            printf("b: %d\n", i);
        }
    }
}