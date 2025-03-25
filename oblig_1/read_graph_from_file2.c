#include <stdlib.h>
#include "function_declarations.h"

/**
 * A function that reads a txt file with node link information for a 
 * hyperlink matrix generation but stores it in CRS format.
 * @param char pointer to the filename.
 * @param N pointer to the number of nodes.
 * @param row_ptr pointer to the rows.
 * @param col_idx pointer to the column index.
 * @param val pointer to the values.
 * @param E pointer to the number of edges.
 * @see 
 * @return 
 */
void read_graph_from_file2 (char *filename, int *N, int **row_ptr, int **col_idx, double **val, int *E){
    FILE* fptr = fopen(filename, "r"); // Open file with file pointer
    if (fptr == NULL){ // Check that the file pointer points to something
        fprintf(stderr, "Unable to open file!\n"); // If it points to nothing then return an error message
        return; // Stop rest of code from running
    }

    char line[256]; // Prepare a dummy line length that encapsulates the line in the txt file
    fgets(line, sizeof(line),fptr); // Read the first line
    fgets(line, sizeof(line),fptr); // Read the second line
    
    if (fgets(line, sizeof(line),fptr)){ // Read the third line, where num nodes should be
        sscanf(line, "# Nodes: %d Edges: %d", N, E); // Scan the line for the number of nodes: N, and the number of edges: E
    }

    fgets(line, sizeof(line),fptr); // Read the forth line: # FromNodeId    ToNodeId

    // Allocate the arrays for storage:
    *row_ptr = (int*)calloc((*N+1), sizeof(int)); // Allocate the row pointers, should equal number of Nodes + 1
    *col_idx = (int*)malloc(*E * sizeof(int)); // Allocate the column pointers, should equal number of Edges
    *val = (double*)malloc(*E * sizeof(double)); // Allocate the value pointers, should equal number of Edges

    int* edge_count = (int*)calloc(*N, sizeof(int)); // Array to count edges for each row
    int edge_idx = 0; // current idex in col_idx and val

    
    for (int i = 0; i < *E; i++){ // For each edge in graph
        if (fgets(line, sizeof(line), fptr)){ // Read the edge line from the file
            int from, to; // Allocate the from and to node numbers
            if (sscanf(line, "%d %d", &from, &to)==2){ // Check that we get both from and to node
                if ((from != to) && from<*N && to<*N){ // Handle self links and illegal links
                    (*col_idx)[edge_idx] = to; // Store the column index
                    (*val)[edge_idx] = 1.0; // Mark the value
                    edge_count[from]++; // Increment edge count
                    edge_idx++; // Increment edge index
                }
            }
        }
    }
    
    (*row_ptr)[0] = 0; // Starting index
    for (int i = 1; i <= *N; i++){
        (*row_ptr)[i] = (*row_ptr)[i-1] + edge_count[i-1]; // Store row indices 
    }
    
    // Normalize:
    double *count = (double*)calloc(*N, sizeof(double)); // Temp array of out going links
    int start,end;
    for (int i=0; i < *N; i++){
        start = (*row_ptr)[i];
        end = (*row_ptr)[i+1];
        for (int j = start; j < end; j++){
            count[(*col_idx)[j]]++; // Increment count
        }
    }
    for (int i=0; i < *N; i++){
        start = (*row_ptr)[i];
        end = (*row_ptr)[i+1];
        for (int j = start; j < end; j++){
            if (edge_count[j]>0){
                (*val)[j] /= count[(*col_idx)[j]]; // Normalize column
            }
        }
    }


    
    // Free:
    free(edge_count);
    free(count);

    fclose(fptr); // Close the file reader
}

/**
 * Function for printing CRS format of hyperlink matrix
 * @param N pointer to the number of nodes.
 * @param E pointer to the number of edges.
 * @param row_ptr pointer to the rows.
 * @param col_idx pointer to the column index.
 * @param val pointer to the values.
 */
void print_crs_format(int *N, int *E, int **row_ptr, int ** col_idx, double **val){
    printf("Row pointers:\n");
    for (int i = 0; i <= *N; i++){
        printf("%d ",(*row_ptr)[i]);
    }

    printf("\n");

    printf("Column indices:\n");
    for (int i = 0; i <= *E; i++){
        printf("%d ",(*col_idx)[i]);
    }

    printf("\n");

    printf("Values:\n");
    for (int i = 0; i <= *N; i++){
        printf("%.1f ",(*val)[i]);
    }

    printf("\n");
}