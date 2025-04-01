#include <stdio.h>


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
void read_graph_from_file1 (char *filename, int *N, double ***hyperlink_matrix, int *E);

/**
 * Function for printing hyperlink matrix
 * @param N pointer to num nodes.
 * @param hyperlink_matrix pointer to hyperlink matrix
 */
void print_hyperlink_matrix(int *N, double ***hyperlink_matrix);

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
void read_graph_from_file2 (char *filename, int *N, int **row_ptr, int ** col_idx, double **val, int *E);

/**
 * Function for printing CRS format of hyperlink matrix
 * 
 * @param N pointer to the number of nodes.
 * @param E pointer to the number of edges.
 * @param row_ptr pointer to the rows.
 * @param col_idx pointer to the column index.
 * @param val pointer to the values.
 */
void print_crs_format(int *N, int *E, int **row_ptr, int ** col_idx, double **val);

/**
 * Page rank iterations version 1
 * 
 * @param N num nodes
 * @param hyperlink_matrix pointer to hyperlink matrix
 * @param d relax parameter
 * @param epsilon stop condition
 * @param scores score pointer
 */
void Page_Rank_iterations1 (int N, double **hyperlink_matrix, double d, double epsilon, double *scores);

/**
 * Page rank iteration function for the CRS formatted hyper link matrix.
 * 
 * @param N        Number of nodes in the graph.
 * @param row_ptr  Pointer to the row offsets array in CRS format.
 * @param col_ptr  Pointer to the column indices array in CRS format.
 * @param val      Pointer to the values array in CRS format, representing transition probabilities.
 * @param d        Damping factor (typically set to 0.85).
 * @param epsilon  Convergence threshold; iteration stops when score changes are smaller than epsilon.
 * @param scores   Output array to store the final PageRank scores of each node.
 */
void Page_Rank_iterations2 (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores);

/**
 * OpenMP version of the crs version of page rank iteration algorithm.
 * 
 * The real parallelism happens in new_x_2_omp.
 * 
 * @param N        Number of nodes in the graph.
 * @param row_ptr  Pointer to the row offsets array in CRS format.
 * @param col_ptr  Pointer to the column indices array in CRS format.
 * @param val      Pointer to the values array in CRS format, representing transition probabilities.
 * @param d        Damping factor (typically set to 0.85).
 * @param epsilon  Convergence threshold; iteration stops when score changes are smaller than epsilon.
 * @param scores   Output array to store the final PageRank scores of each node.
 */
void Page_Rank_iterations2_omp (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores);


/**
 * Function for printing out the top n pages.
 * 
 * @param N number of pages.
 * @param scores list of page rank scores
 * @param n number of pages to show
 */
void top_n_pages (int N, double *scores, int n);


/**
 * OpenMP version of finding to n pages.
 * 
 * @param N number of pages.
 * @param scores list of page rank scores
 * @param n number of pages to show
 */
void top_n_pages_omp (int N, double *scores, int n);
