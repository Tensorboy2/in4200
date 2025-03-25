#include <stdio.h>
#include "function_declarations.h"

int main(){
    char* filename = "../graphs/simple-webgraph.txt"; // path to small graph
    // char* filename = "../graphs/100nodes_graph.txt"; // path to medium graph
    // char* filename = "../graphs/web-stanford.txt"; // path to large graph
    int N, E; // Number nodes and edges
    // Use read_graph_from_file1:
    double** hyperlink_matrix; // Hyperlink matrix pointer
    read_graph_from_file1(filename, &N, &hyperlink_matrix, &E); // Call read from file function

    printf("total nodes %d\n", N); // Print total nodes
    print_hyperlink_matrix(&N, &hyperlink_matrix);
    
    
    // Use read_graph_from_file2:
    int* row_ptr; // Row pointer
    int* col_idx; // Column pointer
    double* val; // Values pointer 
    read_graph_from_file2(filename, &N, &row_ptr, &col_idx, &val, &E);
    print_crs_format(&N, &E, &row_ptr, &col_idx, &val);

    return 0;
}


// 