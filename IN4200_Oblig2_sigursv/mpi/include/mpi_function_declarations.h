#include <stdio.h>

/// @brief Performs the 2 chunk version of the Gauss Seidel algorithm using a MPI process on each chunk.
/// @param my_rank 
/// @param kmax 
/// @param my_jmax 
/// @param imax 
/// @param phi 
void GS_iteration_2_chunks_mpi(int my_rank, int kmax, int my_jmax, int imax, double ***phi);

void GS_iteration_2_chunks_mpi_simple(int my_rank, int kmax, int my_jmax, int imax, double ***phi);