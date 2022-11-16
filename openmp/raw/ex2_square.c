#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024L*1024L*1024L

// gcc raw/ex2_square.c
// time ./a.out

int main() {
    long i;
    int * a = malloc(4 * SIZE);
    int * b = malloc(4 * SIZE);
    for (i = 0 ; i < SIZE; i++){
        a[i] = i;
    }
    for (i = 0; i < SIZE; i++){
        b[SIZE - 1 - i] = a[i]*a[i] - 1;
    }
    // -1 0 3 8
    printf("%d %d %d %d\n", b[SIZE-1], b[SIZE-2], b[SIZE-3], b[SIZE-4]);
}