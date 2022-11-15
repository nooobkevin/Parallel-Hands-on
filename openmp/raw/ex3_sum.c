#include <stdio.h>
#include <stdlib.h>

#define SIZE 1024L*1024L*128L

// gcc raw/ex3_sum.c
// time ./a.out

int main() {
    long i, j = 0;
    int * a = malloc(4 * SIZE);
    for (i = 0 ; i < SIZE; i++){
        a[i] = i;
    }

    for (i = 0; i < SIZE; i++){
        j += a[i];
    }
    
    // 9007199187632128
    printf("%ld\n", j);
}