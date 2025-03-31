#include "function_declarations.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 5) { // Error handel for sys args
        printf("Usage: %s <graph> <damping_factor> <epsilon> <top_n>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1]; // Small web graph file
    double d = atof(argv[2]); // Convert damping factor to double
    double epsilon = atof(argv[3]); // Convert convergence threshold to double
    int n = atoi(argv[4]); // Convert top n pages to int
    int N, E; // Number of nodes and edges
    int *row_ptr; // Row pointer (CRS format)
    int *col_idx; // Column indices (CRS format)
    double *val; // Values pointer (CRS format)

    printf("OMP:\n");
    read_graph_from_file2(filename, &N, &row_ptr, &col_idx, &val, &E); // Use read_graph_from_file2
    // printf("Total nodes %d\n", N); // Print total nodes
    // print_crs_format(&N, &E, &row_ptr, &col_idx, &val); // Optional print of crs format
    double *scores_large = (double *)malloc(N * sizeof(double)); // Allocate score array
    Page_Rank_iterations2_omp(N,row_ptr,col_idx,val,d,epsilon,scores_large); // Calculate page rank scores
    top_n_pages_omp(N,scores_large,n);

    return 0;
}