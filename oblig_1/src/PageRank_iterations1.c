#include <stdlib.h>
#include "function_declarations.h"
#include <stdbool.h>
#include <math.h>
#include <string.h>


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
bool stop_1(double *x, double *x_last, int N, double epsilon){
    double max_diff = 0; // Initial max guess (perfect convergence)
    for (int i = 0; i < N; i++){ // Go over every score
        double diff = fabs(x[i]-x_last[i]); // Calculate diff 
        if (diff>max_diff){ // Find new max
            max_diff = diff;
        }
    }
    return max_diff > epsilon; // Return true if bigger so that while loop continues
}

/**
 * Find dangling nodes. 
 * 
 * Uses the hyperlink matrix to check if any column is only zeros. 
 * Assumes the node is dangling by setting the value to 1. 
 * If a non zero value is found then the search stops and the valuer is the to 0 (non-dangling).
 * 
 * @param hyperlink_matrix pointer to hyperlink matrix
 * @param N number of nodes
 * @param dangling list of dangling nodes 
 */
void find_dangling_1(double **hyperlink_matrix, int N, int *dangling){
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

/**
 * Function for iterative PageRank algorithm.
 * 
 * @param x current score values
 * @param x_last previous score values
 * @param N number of nodes
 * @param d damping constant
 * @param hyperlink_matrix pointer to hyperlink matrix
 */
void new_x_1(double *x, double *x_last, int N, double d, double **hyperlink_matrix){
    int *dangling = calloc(N,sizeof(int)); // Initialize the dangling array
    find_dangling_1(hyperlink_matrix,N,dangling); // Find dangling nodes
    double W = 0;
    for (int i = 0; i < N; i++){
        if (dangling[i]){
            W+=x_last[i]; // Find the number of dangling nodes
        }
    }

    double pre1 = (1 - d) / N + (d * W) / N; // Precompute the factor

    for (int i = 0; i < N; i++){
        double temp = 0;
        // Matrix vector product: Ax^{k-1}
        for (int j = 0; j < N; j++){
            temp += hyperlink_matrix[i][j]*x_last[j];
        }
        x[i] = pre1 + d*temp; // Sum up each term
    }
    free(dangling);
}


void Page_Rank_iterations1(int N, double **hyperlink_matrix, double d, double epsilon, double *scores){

    double *x = (double*)malloc(N * sizeof(double)); // Allocate initial scores
    for (int i = 0; i < N; i++){
        x[i] = 1.0 / N; // Initial guess
    }
    double *x_last = (double*)calloc(N,sizeof(double)); // Allocate previous scores
    int count = 0; // Iteration counter
    do {
        memcpy(x_last, x, N * sizeof(double)); // Copy the last to the new before updating the new one

        new_x_1(x,x_last,N,d,hyperlink_matrix);
        count++;
    } while ((stop_1(x,x_last, N, epsilon))); // Check if converged
    
    printf("Converged after %d iterations.\n",count);
    memcpy(scores, x, N * sizeof(double)); // Set last scores to the score array.
    free(x);
    free(x_last);
}

