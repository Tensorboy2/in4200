#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"

void allocate_array3D(int kmax, int jmax, int imax, double ****array){
    int ***arr =  malloc(kmax*sizeof(double**));
    // int data =  malloc(kmax*jmax*imax*sizeof(double));

    for (int k; k<kmax; k++){
        arr[k] = malloc(jmax*sizeof(double*));
        for (int j = 0; j<jmax;j++){
            arr[k][j] = malloc(imax*sizeof(double*));
        }
    }
}

void fill_array(int kmax, int jmax, int imax, double ****array){
    srand(time(NULL));
    for (int k=1;k<kmax-1;k++){
        for (int j=1;j<jmax-1;j++){
            for (int i=1;i<imax-1;i++){
                if (i == 0 || j == 0 || k == 0 || i == imax-1 || j == jmax-1 || k == kmax-1)
                    *array[k][j][i] = 0.0;  // boundary
                else
                    *array[k][j][i] = (double)rand() / RAND_MAX;  // random interior
            }
        }
    }
}

void free_array3D(double ***array, int kmax, int jmax) {
    if (!array) return;
    free(array[0][0]); 
    for (int k = 0; k < kmax; k++) {
        free(array[k]);
    }
    free(array);
}

double euclidean_distance(int kmax, int jmax, int imax, double ***arr1, double ***arr2){
    int k,j,i;
    double dist;
    for (k=0;k<kmax;k++){
        for (j=0;j<jmax;j++){
            for (i=0;i<imax;i++){
                dist += (arr2[k][j][i]-arr1[k][j][i]);
            }
        }
    }
    return dist;
}
