#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"
#include "helpers.h"

int main(int nargs, char **args){
    double ***arr1, ***arr2;
    int n,k,j,i, num_iters, kmax, jmax, imax;

    num_iters = atoi(args[1]);
    kmax = atoi(args[2]);
    jmax = atoi(args[3]);
    imax = atoi(args[4]);

    allocate_array3D(kmax,jmax,imax,&arr1);
    allocate_array3D(kmax,jmax,imax,&arr2);

    fill_array(kmax,jmax,imax,&arr1);
    fill_array(kmax,jmax,imax,&arr2);


    for (n=0; n<num_iters; n++) {
        GS_iteration_normal(kmax,jmax,imax,arr1);
        GS_iteration_2_chunks(kmax,jmax,imax,arr2);
        }

    printf("num iters=%d, kmax=%d, jmax=%d, imax=%d, diff=%g\n", num_iters, kmax, jmax, imax, euclidean_distance(kmax,jmax,imax,arr1,arr2));
    
    free_array3D(arr1, kmax, jmax);
    free_array3D(arr2, kmax, jmax);
    
    return 0;
}