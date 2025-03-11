#include <stdio.h>

void read_graph_from_file1 (char *filename, int *N, int ***hyperlink_matrix);

void read_graph_from_file2 (char *filname, int *N, int **row_ptr, int ** col_idx, double **val);

void Page_Rank_iterations1 (int N, double **hyperlink_matrix, double d, double epsilon, double *scores);

void Page_Rank_iterations2 (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores);

void Page_Rank_iterations2_omp (int N, int *row_ptr, int *col_ptr, double *val, double d, double epsilon, double *scores);

void top_n_pages (int N, double *scores, int n);

void top_n_pages_omp (int N, double *scores, int n);
