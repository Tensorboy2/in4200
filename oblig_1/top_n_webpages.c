#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
// #include <math.h>
#include <string.h>

/**
 * Function for printing out the top n pages.
 * @param N number of pages.
 * @param scores list of page rank scores
 * @param n number of pages to show
 */
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
        printf("Score: %.4f, page number: %d", max, idx);
        printf("\n");
        scores[idx] = 0;
    }
    printf("\n");

    free(top_n_idx);
    free(top_n_scores);
}
