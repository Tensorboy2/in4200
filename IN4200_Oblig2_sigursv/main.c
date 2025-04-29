#include <stdio.h>
#include <stdlib.h>
#include "serial_function_declarations.h"
#include "helpers.h"
#include <time.h>

int main(int nargs, char **args){
    if (nargs < 5) {
        fprintf(stderr, "Usage: %s <num_iters> <kmax> <jmax> <imax>\n", args[0]);
        return 1;
    }

    // Allocate variables:
    double ***arr1, ***arr2;
    int num_iters, kmax, jmax, imax;

    // Read variables from command line
    num_iters = atoi(args[1]);
    kmax = atoi(args[2]);
    jmax = atoi(args[3]);
    imax = atoi(args[4]);
    
    // Allocate two arrays:
    allocate_array3D(kmax,jmax,imax,&arr1);
    allocate_array3D(kmax,jmax,imax,&arr2);
   
    // Preform standard Gauss Seidel:
    clock_t start = clock();
    for (int n=0; n<num_iters; n++) {
        GS_iteration_normal(kmax,jmax,imax,arr1);
    }
    clock_t end = clock();
    double time_spent_normal = (double)(end - start) / CLOCKS_PER_SEC;
    
    // Perform 2 chunk Gauss Seidel:
    start = clock();
    for (int n=0; n<num_iters; n++) {
        GS_iteration_2_chunks(kmax,jmax,imax,arr2);
    }
    end = clock();
    double time_spent_2_chunks = (double)(end - start) / CLOCKS_PER_SEC;

    // Print diff and time:
    printf("num iters=%d, kmax=%d, jmax=%d, imax=%d, diff=%g\n", num_iters, kmax, jmax, imax, euclidean_distance(kmax,jmax,imax,arr1,arr2));
    printf("Time spent normal: %f seconds\n", time_spent_normal);
    printf("Time spent 2 chunks: %f seconds\n", time_spent_2_chunks);

    // Free arrays:
    free_array3D(arr1, kmax, jmax);
    free_array3D(arr2, kmax, jmax);
    
    return 0;
}