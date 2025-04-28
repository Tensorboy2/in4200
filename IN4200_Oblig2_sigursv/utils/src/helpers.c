#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helpers.h"


void allocate_array3D(int kmax, int jmax, int imax, double ****array) {
    double ***arr3D = malloc(kmax * sizeof(double **));
    for (int k = 0; k < kmax; k++) {
        arr3D[k] = malloc(jmax * sizeof(double *));
        for (int j = 0; j < jmax; j++) {
            arr3D[k][j] = malloc(imax * sizeof(double));
            for (int i = 0; i < imax; i++){
                if (i == 0 || j == 0 || k == 0 || i == imax-1 || j == jmax-1 || k == kmax-1)
                    arr3D[k][j][i] = 0.0;  // boundary
                else
                    arr3D[k][j][i] = 1.0;  // random interior
            }
        }
    }
    *array = arr3D;
}

double* flatten_array3D(int kmax, int jmax, int imax, double ***array){
    double* flatt_array = malloc(kmax * jmax * imax * sizeof(double));
    int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = 0; j < jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    flatt_array[idx++] = array[k][j][i];
                }
            }
        }
    return flatt_array;
}

double*** reconstruct_array3D(int kmax, int jmax, int imax, double* flatt_array){
    double ***arr3D;
    allocate_array3D(kmax,jmax,imax,&arr3D);
    int idx = 0;
        for (int k = 0; k < kmax; k++) {
            for (int j = 0; j < jmax; j++) {
                for (int i = 0; i < imax; i++) {
                    arr3D[k][j][i] = flatt_array[idx++];
                }
            }
        }
    return arr3D;
}


void free_array3D(double ***array, int kmax, int jmax) {
    if (!array) return;
    free(array[0][0]); 
    for (int k = 0; k < kmax; k++) {
        free(array[k]);
    }
    free(array);
}


// #include <math.h>
#include <math.h>
double euclidean_distance(int kmax, int jmax, int imax, double ***arr1, double ***arr2){
    double dist = 0;

    for (int k = 0; k < kmax; k++){
        for (int j = 0; j < jmax; j++){
            for ( int i = 0; i < imax; i++){
                double diff = arr2[k][j][i] - arr1[k][j][i];
                dist += diff*diff;
            }
        }
    }
    return sqrt(dist);
}
