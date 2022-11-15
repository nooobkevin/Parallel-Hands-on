// modified from https://www.tutorialspoint.com/data_structures_algorithms/merge_sort_program_in_c.htm
#include <stdio.h>
#include <stdlib.h>

// gcc exercise_merge_sort.c
// # for debug
// shuf -i 0-1024 | ./a.out 1024
// # for timing
// shuf -i 0-16777215 | time ./a.out 16777216

// Some hints:
//* This is a recursive impl of merge sort, as said, openmp works best using for-loop, you might have some problem parallelizing recursive impl
//  (Optional) Of course you can try in this form
//* There is iterative impl that gives faster performance and also easier to handle imo
//* You are allowed to import any single thread sorting alg, e.g. quicksort to sort a segment length <= 100, which will ease your impl
//  (Optional) Last thing you can try, import a parallel sort from Intel Thread Building Block (R), did you achieve good performance?

void merging(int * from, int * to, int low, int mid, int high) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(from[l1] <= from[l2])
            to[i] = from[l1++];
        else
            to[i] = from[l2++];
    }

    while(l1 <= mid)    
        to[i++] = from[l1++];

    while(l2 <= high)   
        to[i++] = from[l2++];

    for(i = low; i <= high; i++)
        from[i] = to[i];
}

void sort(int * from, int * to, int low, int high) {
    int mid;

    if(low < high) {
        mid = (low + high) / 2;
        sort(from, to, low, mid);
        sort(from, to, mid+1, high);
        merging(from, to, low, mid, high);
    } else { 
        return;
    }   
}

int main(int argc, char * argv[]) {
    int size, sum;
    sscanf(argv[1], "%d", &size);
    int * from = malloc(4*size);
    int * to = malloc(4*size);
    sum = 0;
    for (int i = 0; i < size; i++){
        fscanf(stdin, "%d", from + i);
        sum += from[i];
    }
    printf("sum: %d\n", sum);

    sort(from, to, 0, size - 1);

    sum = 0;
    for(int i = 0; i < size; i++){
        if(to[i] != i)
            printf("[%4d]: %d\n", i, to[i]);
        sum += to[i];
    }
    printf("sum: %d\n", sum);
}