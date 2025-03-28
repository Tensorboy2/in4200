#include <stdlib.h>
#include "function_declarations.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool stop(double *x, double *x_last, int N, double epsilon){
    double max_diff = 0;
    for (int i = 0; i < N; i++){
        double diff = fabs(x[i]-x_last[i]);
        if (diff>max_diff){
            max_diff = diff;
        }
    }
    return max_diff > epsilon; // Return true if bigger so that while loop continues
}


void find_dangling(double **hyperlink_matrix, int N, int *dangling){
    for (int i = 0; i<N; i++){
        int is_dangling = 1; // Assume current col is dangling
        for (int j = 0; j<N; j++){
            if (hyperlink_matrix[i][j]!=0){ // Check is col element is not zero
                is_dangling = 0;
                break; // Stop searching
            } 
        }
        dangling[i]=is_dangling;  // Set colnum index to is dangling
    }
}

void new_x(double *x, double *x_last, int N, double d, double **hyperlink_matrix){
    memcpy(x_last, x, N * sizeof(double));
    int *dangling = calloc(N,sizeof(int));
    find_dangling(hyperlink_matrix,N,dangling); 
    double W = 0;
    for (int i = 0; i < N; i++){
        if (dangling[i]){
            W+=x_last[i];
        }
    }

    double pre1 = (1 - d) / N + (d * W) / N;

    for (int i = 0; i < N; i++){
        double temp = 0;
        for (int j = 0; j < N; j++){
            temp += hyperlink_matrix[i][j]*x_last[j];
        }
        x[i] = pre1 + d*temp;
    }
    free(dangling);
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
        x[i] = 1.0 / N; // Initial guess
    }
    double *x_last = (double*)calloc(N,sizeof(double));
    int count = 0;
    do {
        new_x(x,x_last,N,d,hyperlink_matrix);
        count++;
    } while ((stop(x,x_last, N, epsilon)));
    
    printf("Converged after %d iterations.\n",count);
    memcpy(scores, x, N * sizeof(double));
    // printf("Scores:\n");
    // for (int i = 0; i < N; i++){
    //     printf("%.4f ", scores[i]);
    // }
    // printf("\n");
    free(x);
    free(x_last);
}

