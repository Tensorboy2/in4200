#include <stdlib.h>
#include "function_declarations.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <omp.h>

/**
 * Function for page rank iteration stop check.
 * 
 * Checks whether the maximum difference between the current x and the last x is smaller than epsilon.
 * 
 * @param x the current score values
 * @param x_last the previous score values
 * @param N number of nodes
 * @param epsilon convergence threshold
 *  
 */
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

/**
 * CRS version of finding dangling nodes. 
 * 
 * If the row pointer is the same as the next one than the dangling index is set to 1.
 * 
 * @param row_ptr row pointers
 * @param N number of nodes
 * @param dangling dangling array
 */
void find_dangling_2(int *row_ptr, int N, int *dangling){
    for (int i = 0; i < N; i++){
        dangling[i] = (row_ptr[i] == row_ptr[i + 1]) ? 1 : 0;
    }
}

/**
 * CRS version of PageRank algorithm. 
 * 
 * Uses CRS format of hyperlink matrix to compute PageRank score for graph. 
 * 
 * @param x current scores
 * @param x_last previous scores 
 * @param N number of nodes
 * @param d damping constant
 * @param row_ptr row pointers
 * @param col_ptr column pointers
 * @param val value pointers
 */
void new_x_2(double *x, double *x_last, int N, double d, int *row_ptr, int *col_ptr, double *val){

    int *dangling = calloc(N, sizeof(int)); // Allocate dangling node list
    find_dangling_2(row_ptr, N, dangling);  // Find dangling
    
    double W = 0;
    for (int i = 0; i < N; i++){
        if (dangling[i]){
            W+=x_last[i]; // Accumulate to num dangling
        }
    }

    double pre1 = (1 - d) / N + (d * W) / N; // Precompute factor
 
    // CRS version of matrix vector product:
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


void Page_Rank_iterations2 (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores){
    double *x = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++){
        x[i] = 1 / N; // Initial guess
    }
    double *x_last = (double*)calloc(N,sizeof(double));
    int count = 0; // Iterations counter
    do {
        memcpy(x_last, x, N * sizeof(double)); // Copy last scores to current scores before updating

        new_x_2(x,x_last,N,d,row_ptr,col_ptr,val);
        count++;
    } while (stop_2(x,x_last, N, epsilon)); // Check if converged

    printf("Converged after %d iterations.\n",count);
    memcpy(scores, x, N * sizeof(double));
    free(x);
    free(x_last);
}

/**
 * OpenMP verion of the update x
 * 
 * Essentially a parallelized version of doing a matrix vector product row by row.
 * 
 * Possible bottle neck is the different lengths of different rows.
 * 
 * @param x The current scores to be updated
 * @param x_last The previous scores to be used in the update
 * @param N Number of nodes
 * @param d Relax parameter
 * @param row_ptr Row pointer list from crs format
 * @param col_ptr Column pointer list from crs format
 * @param val All non-zero values in graph hyperlink matrix
 *  
 */
void new_x_2_omp(double *x, double *x_last, int N, double d, int *row_ptr, int *col_ptr, double *val){

    int *dangling = calloc(N, sizeof(int));
    find_dangling_2(row_ptr, N, dangling); 
    
    double W = 0;
    #pragma omp parallel for reduction(+:W) // Reduction avoids race condition
    for (int i = 0; i < N; i++){
        if (dangling[i]){
            W+=x_last[i];
        }
    }

    double pre1 = (1 - d) / N + (d * W) / N;
    #pragma omp parallel for // Split the work of each row pointer
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
 * OMP version of function for page rank iteration stop check.
 * 
 * Checks whether the maximum difference between the current x and the last x is smaller than epsilon.
 * 
 * @param x the current score values
 * @param x_last the previous score values
 * @param N number of nodes
 * @param epsilon convergence threshold
 *  
 */
bool stop_2_omp(double *x, double *x_last, int N, double epsilon){
    double max_diff = 0;
    #pragma omp parallel
    {
        double local_max_diff = 0;
        #pragma omp nowait
        for (int i = 0; i < N; i++){
            double diff = fabs(x[i]-x_last[i]);
            if (diff>max_diff){
                max_diff = diff;
            }
        }

        #pragma omp critical
        {
            if (local_max_diff>max_diff){
                max_diff = local_max_diff;
            }
        }
    }
    return max_diff > epsilon; // Return true if bigger so that while loop continues
}


void Page_Rank_iterations2_omp (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores){
    double *x = (double*)malloc(N * sizeof(double));
    for (int i = 0; i < N; i++){
        x[i] = 1 / N; // Initial guess
    }
    double *x_last = (double*)calloc(N,sizeof(double));
    int count = 0; // Iteration counter
    do {
        memcpy(x_last, x, N * sizeof(double));
        new_x_2_omp(x,x_last,N,d,row_ptr,col_ptr,val);
        count++;
    } while (stop_2_omp(x,x_last, N, epsilon));

    printf("Converged after %d iterations.\n",count);
    memcpy(scores, x, N * sizeof(double));
    free(x);
    free(x_last);
}
