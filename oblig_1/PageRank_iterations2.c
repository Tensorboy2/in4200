#include <stdlib.h>
#include "function_declarations.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>

bool stop_2(double *x, double *x_last, int N, double epsilon){
    double max_diff = 0;
    for (int i = 0; i < N; i++){
        double diff = fabs(x[i]-x_last[i]);
        if (diff>max_diff){
            max_diff = diff;
        }
    }
    return max_diff > epsilon; // Return true if bigger so that while loop continues
}


void find_dangling_2(int *row_ptr, int N, int *dangling){
    for (int i = 0; i < N; i++){
        dangling[i] = (row_ptr[i] == row_ptr[i + 1]) ? 1 : 0;
    }
}

void new_x_2(double *x, double *x_last, int N, double d, int *row_ptr, int *col_ptr, double *val){

    int *dangling = calloc(N, sizeof(int));
    find_dangling_2(row_ptr, N, dangling); 
    
    double W = 0;
    for (int i = 0; i < N; i++){
        if (dangling[i]){
            W+=x_last[i];
        }
    }

    double pre1 = (1 - d) / N + (d * W) / N;

    for (int i = 0; i < N; i++){
        double temp = 0;
        int start = row_ptr[i];
        int stop = row_ptr[i+1];
        for (int j = start; j < stop; j++){
            temp += val[j]*x_last[col_ptr[j]];
        }
        x[i] = pre1 + d*temp;
    }
    free(dangling);
}

/**
 * Page rank iteration function for the crs formatted hyper link matrix.
 * @param N        Number of nodes in the graph.
 * @param row_ptr  Pointer to the row offsets array in CRS format.
 * @param col_ptr  Pointer to the column indices array in CRS format.
 * @param val      Pointer to the values array in CRS format, representing transition probabilities.
 * @param d        Damping factor (typically set to 0.85).
 * @param epsilon  Convergence threshold; iteration stops when score changes are smaller than epsilon.
 * @param scores   Output array to store the final PageRank scores of each node.
 */
void Page_Rank_iterations2 (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores){
    double *x = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++){
        x[i] = 1 / N; // Initial guess
    }
    double *x_last = (double*)calloc(N,sizeof(double));
    int count = 0;
    do {
        memcpy(x_last, x, N * sizeof(double));

        new_x_2(x,x_last,N,d,row_ptr,col_ptr,val);
        count++;

        // printf("Iteration %d:\n", count);
        // for (int i = 0; i < N; i++) {
        //     printf("%f ", x[i]);
        // }
        // printf("\n");
    } while (stop_2(x,x_last, N, epsilon));

    printf("Converged after %d iterations.\n",count);
    memcpy(scores, x, N * sizeof(double));
    free(x);
    free(x_last);
}
