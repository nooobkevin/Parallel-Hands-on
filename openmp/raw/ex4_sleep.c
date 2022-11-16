#include <stdio.h>
#include <unistd.h>

#define MAX 5

// gcc raw/ex4_sleep.c
// ./a.out

int main() {
    int i;
    for (i = 0 ; i < MAX; i++){
        sleep(i);
        printf("a: %d\n", i);
    }
    for (i = 0 ; i < MAX; i++){
        printf("b: %d\n", i);
    }
}