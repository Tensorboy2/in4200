#include "function_declarations.h"


/**
 * Page rank iteration function for the crs formated hyper link matrix.
 * @param N        Number of nodes in the graph.
 * @param row_ptr  Pointer to the row offsets array in CRS format.
 * @param col_ptr  Pointer to the column indices array in CRS format.
 * @param val      Pointer to the values array in CRS format, representing transition probabilities.
 * @param d        Damping factor (typically set to 0.85).
 * @param epsilon  Convergence threshold; iteration stops when score changes are smaller than epsilon.
 * @param scores   Output array to store the final PageRank scores of each node.
 */
void Page_Rank_iterations2 (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores){

}
