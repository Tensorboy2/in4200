#include <stdlib.h>
#include "function_declarations.h"

/**
 * A function that reads a txt file with node link information for a 
 * hyperlink matrix generation. 
 * 
 * Takes each from and to node and stores it as an entry in a N by N matrix.
 * Then normalizes each column.
 * 
 * @param char pointer to the filename.
 * @param N pointer to the number of nodes.
 * @param hyperlink_matrix pointer to the hyperlink matrix.
 * @param E pointer to the number of edges.
 * @see 
 * @return 
 */
void read_graph_from_file1 (char *filename, int *N, double ***hyperlink_matrix, int *E){
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
   
    // Hyperlink matrix allocation:
    *hyperlink_matrix = (double**)malloc((*N)*sizeof(double*)); // Allocate N columns 
    for (int i = 0; i < *N; i++){ // For each column in the matrix:
        (*hyperlink_matrix)[i] = (double*)calloc(*N, sizeof(double)); // Allocate a N length column vector for each N
    }
    
    fgets(line, sizeof(line),fptr); // Read the forth line: # FromNodeId    ToNodeId

    double *count = (double*)calloc(*N, sizeof(double)); // Temp array of out going links

    // Loop over all edges and store them in hyperlink matrix:
    for (int i = 0; i < *E; i++){ // For each edge in graph
        if (fgets(line, sizeof(line), fptr)){ // Read the edge line from the file
            int from, to; // Allocate the from and to node numbers
            if (sscanf(line, "%d %d", &from, &to)==2){ // Check that we get both from and to node
                if ((from != to) && from<*N && to<*N){ // Handle self links and illegal links
                    (*hyperlink_matrix)[to][from] = 1.0; // Set the hyperlink entry to 1 for that linkage
                    count[from]++; // Increment the from node index
                }
            }
        }
    }
    // Normalize:
    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *N; j++) {
            if (count[j]!=0){ // Handel dangling page normalization
                (*hyperlink_matrix)[i][j]/=count[j];
            }
        }
        printf("\n");
    }

    // Free:
    free(count);

    fclose(fptr); // Close the file reader
}
/**
 * Function for printing hyperlink matrix
 * @param N pointer to num nodes.
 * @param hyperlink_matrix pointer to hyperlink matrix
 */
void print_hyperlink_matrix(int *N, double ***hyperlink_matrix){
    printf("The hyper link matrix is:\n"); 
    for (int i = 0; i < *N; i++){
        for (int j = 0; j < *N; j++) {
            printf("%.1f ", (*hyperlink_matrix)[i][j]); // Print each element of hyperlink matrix
        }
        printf("\n");
    }
    printf("\n");
}
