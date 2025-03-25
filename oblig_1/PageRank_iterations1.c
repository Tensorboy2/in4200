#include <stdlib.h>
#include "function_declarations.h"
#include <stdbool.h>
#include <math.h>

bool stop(double *x, double *x_last, int N, double epsilon){
    double max = 0;
    double tmp;
    for (int i = 0; i < N; i++){
        tmp = fabs(x[i]-x_last[i]);
        if (tmp>max){
            max = tmp;
        }
    }
    return max > epsilon;
}

void new_x(double *x, double *x_last, int N, double d){
    
}

/**
 * Page rank iterations version 1
 * @param N num nodes
 * @param hyperlink_matrix pointer to hyperlink matrix
 * @param d relax parameter
 * @param epsilon stop condition
 * @param scores score pointer
 */
void Page_Rank_iterations1 (int N, double **hyperlink_matrix, double d, double epsilon, double *scores){

    double *x = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++){
        x[i] = 1.0 / N;
    }

    double *x_last = (double*)calloc(N,sizeof(double));
    while (stop(x,x_last, N, epsilon)){
        new_x(x,x_last,N,d);
    }
    free(x);
    free(x_last);
}

