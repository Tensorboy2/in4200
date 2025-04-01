#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>


void top_n_pages (int N, double *scores, int n){
    int* top_n_idx = malloc(n*sizeof(int));
    double* top_n_scores = malloc(n*sizeof(double));
    printf("Top %d pages:\n",n);
    for (int i = 0; i < n; i++){
        double max = scores[0];
        int idx = 0;
        for (int j = 1; j < N; j++){
            if (scores[j]>max){
                max = scores[j];
                idx = j;
            }
        }
        printf("Score: %6f, page number: %d", max, idx);
        printf("\n");
        scores[idx] = 0;
    }
    printf("\n");

    free(top_n_idx);
    free(top_n_scores);
}


void top_n_pages_omp (int N, double *scores, int n){

    // Storage arrays:
    int* top_n_idx = malloc(n*sizeof(int));
    double* top_n_scores = malloc(n*sizeof(double));

    printf("Top %d pages:\n",n);

    // Find n highest scores
    for (int i = 0; i < n; i++){
        // Global first guess:
        double max = -1.0; // No negative scores can exist
        int idx = -1; // Assume the best is outside scope
        #pragma omp parallel // Split to multi processes 
        {
            // Local first guess
            double local_max = -1;
            int local_idx = -1;
            #pragma omp nowait // Each thread goes looking on a separate part of the scores
            {
                for (int j = 0; j < N; j++){
                    if (scores[j]>local_max){
                        local_max = scores[j];
                        local_idx = j;
                    }
                }
            }

            #pragma omp critical  // Each threads best result is compared to each thread
            {
                if (local_max > max) {
                    max = local_max;
                    idx = local_idx;
                }
            }
        }
        if (idx!=-1){
            // Store result
            scores[idx]=-1.0; // So that the old max is out of the game
            top_n_scores[i] = max;
            top_n_idx[i] = idx;
        } else{
            printf("Something went wrong here!");
        }
    }
    // Show result:
    for (int i = 0; i < n; i++) { 
        printf("Score: %6f, page number: %d\n", top_n_scores[i], top_n_idx[i]);
    }
    printf("\n");

    free(top_n_idx);
    free(top_n_scores);
}
