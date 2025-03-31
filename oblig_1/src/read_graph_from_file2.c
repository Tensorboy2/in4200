#include <stdlib.h>
#include "function_declarations.h"

/**
 * A function that reads a txt file with node link information for a 
 * hyperlink matrix generation but stores it in CRS format.
 * 
 * Stores a compressed row verion of the sparse hyperlink matrix.
 * Stores each non-zero value in val, the column index in col_idx,
 * and the row number in row_ptr.
 * 
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

    int* incoming_count = (int*)calloc(*N, sizeof(int)); // Store the incoming counts for each node 
    int* outgoing_count = (int*)calloc(*N, sizeof(int)); // Store the outgoing counts for each node


    // First pass:
    int valid_edges = 0; // Initialize the number of valid edges in the graph
    for (int i = 0; i < *E; i++) { // Loop over each edge in the file  
        if (fgets(line, sizeof(line), fptr)) { // Read the line in the file
            int from, to; // Initialize NodeIDs
            if (sscanf(line, "%d %d", &from, &to) == 2) { // Check that both from and to node is in the line
                if (from != to && from < *N && to < *N) { // Check that it is not a self link or out of bounds link
                    // Increments:
                    incoming_count[to]++;
                    outgoing_count[from]++;
                    valid_edges++;
                }
            }
        }
    }
    
    *row_ptr = (int*)calloc((*N+1), sizeof(int)); // Allocate the row pointers, should equal number of Nodes + 1 with num edges as last entry
    *col_idx = (int*)calloc(valid_edges, sizeof(int)); // Allocate the column pointers, should equal number of Edges
    *val = (double*)calloc(valid_edges, sizeof(double)); // Allocate the value pointers, should equal number of Edges

    int* current_position = (int*)malloc(*N * sizeof(int)); // Current position

    (*row_ptr)[0] = 0; // Rowpointer starts at zero
    for (int i = 1; i <= *N; i++) { // For each node in graph
        (*row_ptr)[i] = (*row_ptr)[i - 1] + incoming_count[i - 1]; // The i'th row pointer is the last pointer pluss the number of incoming links
    }
    // int total_nonzeros = (*row_ptr)[*N]; // Set the number of valid edges 
    for (int i = 0; i < *N; i++) {
        current_position[i] = (*row_ptr)[i]; // Copy the row pointer array
    }
    
    rewind(fptr); // Rewind to the beginning of the file for the second pass

    fgets(line, sizeof(line), fptr); // Skip first line
    fgets(line, sizeof(line), fptr); // Skip second line
    fgets(line, sizeof(line), fptr); // Skip third line
    fgets(line, sizeof(line), fptr); // Skip fourth line


    // Second pass:
    while (fgets(line, sizeof(line), fptr)) {
        int from, to;
        if (sscanf(line, "%d %d", &from, &to) == 2) {
            if (from != to && from < *N && to < *N) {
                int insert_pos = current_position[to]; // Get the position in the col and val array
                (*col_idx)[insert_pos] = from;  // Store the column index (destination node)
                (*val)[insert_pos] = 1.0/outgoing_count[from]; // normalize by column number
                current_position[to]++; // Increment edge index for the next entry in col_idx and val
            }
        }
    }
    
    // Free:
    free(current_position);
    free(incoming_count);
    free(outgoing_count);
    fclose(fptr); // Close the file reader
}

/**
 * Function for printing CRS format of hyperlink matrix
 * 
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
    for (int i = 0; i < *E; i++){
        printf("%.1f ",(*val)[i]);
    }
    printf("\n");
}