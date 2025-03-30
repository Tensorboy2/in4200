#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

// char* filename = "../graphs/simple-webgraph.txt"; // path to small graph
// char* filename = "../graphs/100nodes_graph.txt"; // path to medium graph
// char* filename = "../graphs/web-stanford.txt"; // path to large graph

int main(int argc, char *argv[]){
    if (argc != 6) { // Error handel for sys args
        printf("Usage: %s <small_graph> <large_graph> <damping_factor> <epsilon> <top_n>\n", argv[0]);
        return 1;
    }

    char *small_filename = argv[1]; // Small web graph file
    char *large_filename = argv[2]; // Large web graph file
    double d = atof(argv[3]); // Convert damping factor to double
    double epsilon = atof(argv[4]); // Convert convergence threshold to double
    int n = atoi(argv[5]); // Convert top n pages to int



    // Small file: 
    printf("Small file:\n");
    char *filename = small_filename; // Filename pointer
    int N, E; // Number of nodes and edges
    double **hyperlink_matrix; // Hyperlink matrix pointer
    read_graph_from_file1(filename, &N, &hyperlink_matrix, &E); // Use read_graph_from_file1
    print_hyperlink_matrix(&N, &hyperlink_matrix); // Optional print of hyperlink matrix
    double *scores_small = (double *)malloc(N * sizeof(double)); // Allocate score array
    // printf("Total nodes %d\n", N); // Print total nodes
    Page_Rank_iterations1(N,hyperlink_matrix,d,epsilon,scores_small); // Calculate page rank scores
    top_n_pages(N,scores_small,n);
    
    
    
    // Large file:
    printf("Large file:\n");
    filename = large_filename; // Filename pointer
    int *row_ptr; // Row pointer (CRS format)
    int *col_idx; // Column indices (CRS format)
    double *val; // Values pointer (CRS format)
    read_graph_from_file2(filename, &N, &row_ptr, &col_idx, &val, &E); // Use read_graph_from_file2
    // printf("Total nodes %d\n", N); // Print total nodes
    print_crs_format(&N, &E, &row_ptr, &col_idx, &val); // Optional print of crs format
    double *scores_large = (double *)malloc(N * sizeof(double)); // Allocate score array
    Page_Rank_iterations2(N,row_ptr,col_idx,val,d,epsilon,scores_large); // Calculate page rank scores
    top_n_pages(N,scores_large,n);

    return 0;
}
